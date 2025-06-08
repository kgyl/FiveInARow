#include "stdafx.h"
#include "bmpScreen.h"
void bmpScreen::screenShot(int width,int height,int left,int top,CString name)


{
    CBitmap*  m_pBitmap;                                                                             // 加入类成员
    CFrameWnd* pMainFrame = (CFrameWnd*)AfxGetMainWnd();                     // 获得截图窗口的指针，默认为主窗口
    CPaintDC   dc(pMainFrame); 

    m_pBitmap=new   CBitmap;   
    m_pBitmap->CreateCompatibleBitmap(&dc,width,height);   

    CDC   memDC;  
    memDC.CreateCompatibleDC(&dc); 
    CBitmap memBitmap, *oldmemBitmap;                                                     // 建立和屏幕兼容的bitmap

    memBitmap.CreateCompatibleBitmap(&dc, width,height);

    oldmemBitmap = memDC.SelectObject(&memBitmap);                               //将memBitmap选入内存DC
    memDC.BitBlt(0, 0, width,height, &dc,left, top, SRCCOPY);      // 调解高度宽度
    BITMAP bmp;
    memBitmap.GetBitmap(&bmp);                                                                // 获得位图信息 
    
    FILE *fp = fopen(name, "w+b");

    BITMAPINFOHEADER bih = {0};                                                              // 位图信息头
    bih.biBitCount = bmp.bmBitsPixel;                                                           // 每个像素字节大小
    bih.biCompression = BI_RGB;
    bih.biHeight = bmp.bmHeight;                                                                 // 高度
    bih.biPlanes = 1;
    bih.biSize = sizeof(BITMAPINFOHEADER);
    bih.biSizeImage = bmp.bmWidthBytes * bmp.bmHeight;                            // 图像数据大小
    bih.biWidth = bmp.bmWidth;                                                                  // 宽度
    
    BITMAPFILEHEADER bfh = {0};                                                               // 位图文件头
    bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);     // 到位图数据的偏移量
    bfh.bfSize = bfh.bfOffBits + bmp.bmWidthBytes * bmp.bmHeight;                 // 文件总的大小
    bfh.bfType = (WORD)0x4d42;
    
    fwrite(&bfh, 1, sizeof(BITMAPFILEHEADER), fp);                                            //写入位图文件头
    
    fwrite(&bih, 1, sizeof(BITMAPINFOHEADER), fp);                                           //写入位图信息头
    
    byte * p = new byte[bmp.bmWidthBytes * bmp.bmHeight];                           //申请内存保存位图数据

    GetDIBits(memDC.m_hDC, (HBITMAP) memBitmap.m_hObject, 0, height, p, 
    (LPBITMAPINFO) &bih, DIB_RGB_COLORS);                                                  //获取位图数据

    fwrite(p, 1, bmp.bmWidthBytes * bmp.bmHeight, fp);                                   //写入位图数据
    delete [] p; 
    fclose(fp);
    memDC.SelectObject(oldmemBitmap);
   memDC.DeleteDC();




}