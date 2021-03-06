/*************************************************************************
	> File Name: Client.cc
	> Author: uuchen
	> Mail: 1319081676@qq.com
	> Created Time: 2017年04月15日 星期六 17时12分46秒
 ************************************************************************/

#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<string>
#include<string.h>

#include"File.h"
#include"Socket.h"
#include"InetAddress.h"
#include"i18nText.h"

using namespace unet;
using namespace cv;

int main(int argc,char** argv)
{
    net::socket::InetAddress server("192.168.123.182",16666);
    net::socket::Socket confd(net::socket::CONNECT);
    net::socket::connect(confd,server);

    namedWindow("client");
    char* buf = new char[921600];
    char ch;
    int mode = 1;
    bool runing = false;
    
    i18nText message;
    message.setFont("/usr/share/fonts/truetype/wqy/wqy-microhei.ttc");
    message.setSize(30);
    
    std::wstring control = L"控制模式";
    std::wstring tracing = L"寻迹模式";
    std::wstring obscatle = L"避障模式";
    std::wstring notControl = L"失控状态";

    Mat image(480,640,CV_8UC3);
    
    while(1)
    {
//        unet::file::readn(confd.getFd(),buf,921600);
//        Mat image(480,640,CV_8UC3);
//        image.data = (uchar*)buf;
//        image.reshape(480,640);
//        imshow("client",image);
       
//        image.setTo(Scalar(0,0,0)); 
        imshow("client",image);
        if(mode == 1)
        {//控制模式
            switch (ch = char(waitKey(25)))
            {
                case char(27):
                    std::cout << "响应ESC～" << std::endl;
                    unet::file::writen(confd.getFd(),&ch,1);
                    goto exit;
                    break;
                case 'w':
                    std::cout << "响应前进～" << std::endl;
                    unet::file::writen(confd.getFd(),&ch,1);
                    break;
                case 's':
                    std::cout << "响应后退～" << std::endl;
                    unet::file::writen(confd.getFd(),&ch,1);
                    break;
                case 'a':
                    std::cout << "响应左转～" << std::endl;
                    unet::file::writen(confd.getFd(),&ch,1);
                    break;
                case 'd':
                    std::cout << "响应右转～" << std::endl;
                    unet::file::writen(confd.getFd(),&ch,1);
                    break;
                case char(32):
                {
                    if(runing)
                    {
                        std::cout << "响应停止～" << std::endl;
                        unet::file::writen(confd.getFd(),&ch,1);
                        runing = false;
                    }
                    else
                    {
                        std::cout << "响应开始～" << std::endl;
                        unet::file::writen(confd.getFd(),&ch,1);
                        runing = true;
                    }
                    break;
                }
                case char(50):
                    std::cout << "切换到寻迹模式～" << std::endl;
                    unet::file::writen(confd.getFd(),&ch,1);
                    mode = 2;
                    break;
                case char(51):
                    std::cout << "切换到避障模式～" << std::endl;
                    unet::file::writen(confd.getFd(),&ch,1);
                    mode = 3;
                    break;
                default:
                    break;
            }
        }
        else if(mode == 2)
        {//寻迹模式
            switch (ch = char(waitKey(25)))
            {
                case char(27):
                    std::cout << "响应ESC～" << std::endl;
                    unet::file::writen(confd.getFd(),&ch,1);
                    goto exit;
                    break;
                case char(32):
                {
                    if(runing)
                    {
                        std::cout << "响应停止～" << std::endl;
                        unet::file::writen(confd.getFd(),&ch,1);
                        runing = false;
                    }
                    else
                    {
                        std::cout << "响应开始～" << std::endl;
                        unet::file::writen(confd.getFd(),&ch,1);
                        runing = true;
                    }
                    break;
                }
                case char(49):
                    std::cout << "切换到控制模式～" << std::endl;
                    unet::file::writen(confd.getFd(),&ch,1);
                    mode = 1;
                    break;
                case char(51):
                    std::cout << "切换到避障模式～" << std::endl;
                    unet::file::writen(confd.getFd(),&ch,1);
                    mode = 3;
                    break;
                default:
                    break;
            }
        }
        else if(mode == 3)
        {//避障模式
            switch (ch = char(waitKey(25)))
            {
                case char(27):
                    std::cout << "响应ESC～" << std::endl;
                    unet::file::writen(confd.getFd(),&ch,1);
                    goto exit;
                    break;
                case char(32):
                {
                    if(runing)
                    {
                        std::cout << "响应停止～" << std::endl;
                        unet::file::writen(confd.getFd(),&ch,1);
                        runing = false;
                    }
                    else
                    {
                        std::cout << "响应开始～" << std::endl;
                        unet::file::writen(confd.getFd(),&ch,1);
                        runing = true;
                    }
                    break;
                }
                case char(49):
                    std::cout << "切换到控制模式～" << std::endl;
                    unet::file::writen(confd.getFd(),&ch,1);
                    mode = 1;
                    break;
                case char(50):
                    std::cout << "切换到寻迹模式～" << std::endl;
                    unet::file::writen(confd.getFd(),&ch,1);
                    mode = 2;
                    break;
                default:
                    break;
            }
        }

        if(mode == 1)
        {
            image.setTo(Scalar(0,0,0)); 
            message.putText(image,control.c_str(),Point(500,50),CV_RGB(255,255,255));        
        }
        else if(mode == 2)
        {
            image.setTo(Scalar(0,0,0)); 
            message.putText(image,tracing.c_str(),Point(500,50),CV_RGB(255,255,255));
        }
        else if(mode == 3)
        {
            image.setTo(Scalar(0,0,0)); 
            message.putText(image,obscatle.c_str(),Point(500,50),CV_RGB(255,255,255));
        }
        else
        {
            image.setTo(Scalar(0,0,0)); 
            message.putText(image,notControl.c_str(),Point(500,50),CV_RGB(255,255,255));
        }
    }
    
exit:
    return 0;
}

