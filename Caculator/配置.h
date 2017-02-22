#include "stdafx.h"

extern HFONT 显示器字体 = CreateFont
(
	40, 0,    //高度20, 宽取0表示由系统选择最佳值  
	0, 0,    //文本倾斜，与字体倾斜都为0  
	FW_HEAVY,    //粗体  
	0, 0, 0,        //非斜体，无下划线，无中划线  
	GB2312_CHARSET,    //字符集  
	OUT_DEFAULT_PRECIS,
	CLIP_DEFAULT_PRECIS,
	DEFAULT_QUALITY,        //一系列的默认值  
	DEFAULT_PITCH | FF_DONTCARE,
	(TCHAR*)"微软雅黑"    //字体名称  
);

extern HFONT 按键字体 = CreateFont
 (
	 30, 0,    //高度20, 宽取0表示由系统选择最佳值  
	 0, 0,    //文本倾斜，与字体倾斜都为0  
	 FW_HEAVY,    //粗体  
	 0, 0, 0,        //非斜体，无下划线，无中划线  
	 GB2312_CHARSET,    //字符集  
	 OUT_DEFAULT_PRECIS,
	 CLIP_DEFAULT_PRECIS,
	 DEFAULT_QUALITY,        //一系列的默认值  
	 DEFAULT_PITCH | FF_DONTCARE,
	 (TCHAR*)"微软雅黑"    //字体名称  
 );

