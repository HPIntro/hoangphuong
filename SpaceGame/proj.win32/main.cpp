/***************************************************************************
*
* ___main.cpp___
* ___SpaceGame___
*
* Created by ___NguyenHoangPhuong___ on ___25/07/2013___.
*
* Copyright Vinova Pte. Ltd. All rights reserved.
***************************************************************************
*/

#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"

USING_NS_CC;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppDelegate app;
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    eglView->setViewName("SpaceGame");
    eglView->setFrameSize(680, 500);
    return CCApplication::sharedApplication()->run();
}
