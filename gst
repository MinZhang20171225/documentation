

export PATH=/Media/SD-P1/bin:$PATH

export LD_LIBRARY_PATH=/Media/SD-P1/lib:$LD_LIBRARY_PATH

export GST_PLUGIN_PATH=/Media/SD-P1/lib/gstreamer-1.0:/usr/lib/gstreamer-1.0
export GST_PLUGIN_SCANNER=/usr/lib/gstreamer-1.0/gst-plugin-scanner
export GST_REGISTRY=/tmp/gst_registry.bin


gst-launch-1.0 -v playbin uri=file:///home/work/music/jiaru.wma
gst-launch-1.0 -v -m playbin uri=file:///Media/SD-P1/music/1.mp3
gst-launch-1.0 playbin uri=http://s2.viastreaming.net:6165
mms://alive.rbc.cn/fm1006
mms://live.cdbs.com.cn/914


export GST_DEBUG=2

gst-inspect-1.0 /mnt/yf-gq/work/wma/gst-libav-1.4.5/ext/libav/.libs/libgstlibav.so

gst-launch-1.0 filesrc location=/home/work/music/jiaru.wma ! asfdemux ! avdec_wmav2 ! audioconvert ! flacenc ! filesink location=test.flac

