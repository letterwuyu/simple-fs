#include "log4z.h"
#include <iostream>
#include <stdio.h>

using namespace zsummer::log4z;
int main()
{
	ILog4zManager::GetInstance()->Start(); 
	LOGD(" *** " << "hellow wolrd" <<" *** ");  
    LOGI("loginfo");  
    LOGW("log warning");  
    LOGE("log err");  
    LOGA("log alarm");  
    LOGF("log fatal" << "ssss");
}
