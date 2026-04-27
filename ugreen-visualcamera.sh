#!/bin/bash

# 绿联采集卡虚拟摄像头启动脚本
# 作者：根据最终成功配置整理
# 版本：1.0

set -e  # 遇到错误立即退出

# 颜色输出
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${GREEN}========================================${NC}"
echo -e "${GREEN}     绿联采集卡虚拟摄像头启动脚本     ${NC}"
echo -e "${GREEN}========================================${NC}"

# 检查必要工具
command -v v4l2-ctl >/dev/null 2>&1 || { echo -e "${RED}错误: v4l2-ctl 未安装，请执行 sudo apt install v4l-utils${NC}" >&2; exit 1; }
command -v ffmpeg >/dev/null 2>&1 || { echo -e "${RED}错误: ffmpeg 未安装，请执行 sudo apt install ffmpeg${NC}" >&2; exit 1; }

# 新版 v4l2loopback-ctl 路径（假设在 ~/v4l2loopback/utils/ 下）
V4L2LOOPBACK_CTL="$HOME/v4l2loopback/utils/v4l2loopback-ctl"
if [ ! -f "$V4L2LOOPBACK_CTL" ]; then
    echo -e "${YELLOW}警告: 未找到新版 v4l2loopback-ctl，尝试使用系统版本${NC}"
    V4L2LOOPBACK_CTL="v4l2loopback-ctl"
fi

# 1. 清理旧进程
echo -e "${YELLOW}[1/6] 清理可能冲突的进程...${NC}"
sudo pkill -f ffmpeg 2>/dev/null || true
sudo pkill -f ffplay 2>/dev/null || true

# 2. 重新加载 v4l2loopback 模块
echo -e "${YELLOW}[2/6] 重新加载 v4l2loopback 模块...${NC}"
sudo modprobe -r v4l2loopback 2>/dev/null || true
sudo modprobe v4l2loopback video_nr=4 card_label="VirtualCamera" max_buffers=8

# 3. 自动查找绿联采集卡设备
echo -e "${YELLOW}[3/6] 查找绿联采集卡设备...${NC}"
UGREEN_DEV=$(v4l2-ctl --list-devices | grep -A 1 "UGREEN" | grep video | head -1 | tr -d ' ' || true)
if [ -z "$UGREEN_DEV" ]; then
    echo -e "${RED}错误: 未找到绿联采集卡，请检查连接。${NC}"
    echo "当前视频设备列表："
    v4l2-ctl --list-devices
    exit 1
fi
echo -e "    找到采集卡: ${GREEN}$UGREEN_DEV${NC}"

# 4. 设置虚拟摄像头格式为 YUYV 1080p 30fps
echo -e "${YELLOW}[4/6] 设置虚拟摄像头格式...${NC}"
if [[ "$V4L2LOOPBACK_CTL" == *"utils"* ]]; then
    # 使用新版工具
    sudo "$V4L2LOOPBACK_CTL" set-caps /dev/video4 "YUYV:1920x1080@30/1"
else
    # 如果使用系统旧版，尝试旧语法（但可能失败，我们仍用新版方式）
    echo -e "${YELLOW}使用系统版 v4l2loopback-ctl，尝试旧语法...${NC}"
    sudo v4l2loopback-ctl set-caps "YUYV:1920x1080" /dev/video4
fi

# 验证格式
echo -e "${YELLOW}    当前虚拟摄像头格式：${NC}"
v4l2-ctl -d /dev/video4 --all | grep -E "Width|Height|Pixel Format" | sed 's/^/    /'

# 5. 检测绿联采集卡的默认格式（判断是 MJPG 还是 YUYV）
echo -e "${YELLOW}[5/6] 检测采集卡视频格式...${NC}"
PIXFMT=$(v4l2-ctl -d $UGREEN_DEV --get-fmt-video | grep "Pixel Format" | grep -o "'.*'" | tr -d "'")
echo -e "    采集卡格式: ${GREEN}$PIXFMT${NC}"

# 根据格式选择 ffmpeg 命令
if [[ "$PIXFMT" == *"MJPG"* ]]; then
    FFMPEG_CMD="ffmpeg -f v4l2 -input_format mjpeg -video_size 1920x1080 -framerate 60 -i $UGREEN_DEV -vf \"format=yuyv422,fps=30\" -f v4l2 /dev/video4"
elif [[ "$PIXFMT" == *"YUYV"* ]]; then
    FFMPEG_CMD="ffmpeg -f v4l2 -input_format yuyv422 -video_size 1920x1080 -framerate 30 -i $UGREEN_DEV -f v4l2 /dev/video4"
else
    echo -e "${YELLOW}未知格式，尝试使用 MJPG 解码（最常用）${NC}"
    FFMPEG_CMD="ffmpeg -f v4l2 -input_format mjpeg -video_size 1920x1080 -framerate 30 -i $UGREEN_DEV -vf \"format=yuyv422,fps=30\" -f v4l2 /dev/video4"
fi

# 6. 启动转发
echo -e "${YELLOW}[6/6] 启动视频转发（按 Ctrl+C 停止）...${NC}"
echo -e "${GREEN}虚拟摄像头已就绪！设备路径：/dev/video4${NC}"
echo -e "${GREEN}请保持此窗口运行，现在可以打开 Unity 应用。${NC}"
echo "--------------------------------------------------"
echo "转发命令: $FFMPEG_CMD"
echo "--------------------------------------------------"

# 执行命令
eval $FFMPEG_CMD

# 当 ffmpeg 退出时（用户按 Ctrl+C），给出提示
echo -e "${YELLOW}转发已停止。虚拟摄像头将不再输出。${NC}"
