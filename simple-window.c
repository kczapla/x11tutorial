#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <X11/Xlib.h>


void draw_in_window();


int main()
{
    Display* display;
    display = XOpenDisplay(":0");
    if (display == NULL) {
        fprintf(stderr, "cannot connect to x server %s\n",":0");
        exit(-1);
    }

    int screen_num;
    int screen_width;
    int screen_height;
    Window root_window;
    unsigned long white_pixel;
    unsigned long black_pixel;

    screen_num = DefaultScreen(display);
    screen_width = DisplayWidth(display, screen_num);
    screen_height = DisplayHeight(display, screen_num);
    root_window = RootWindow(display, screen_num);
    white_pixel = WhitePixel(display, screen_num);
    black_pixel = BlackPixel(display, screen_num);


    Window win;
    int win_width;
    int win_height;
    int win_x;
    int win_y;
    int win_border_width = 2;

    win_width = DisplayWidth(display, screen_num) / 3;
    win_height = DisplayHeight(display, screen_num) / 3;

    win_x = win_y = 0;

    win = XCreateSimpleWindow(display,
                              root_window,
                              win_x, win_y,
                              win_width, win_height,
                              win_border_width,
                              black_pixel, white_pixel);
    // graphics context
    GC gc;

    /** XGCValues values = CapButt | JoinBevel; */
    XGCValues values = {
        .cap_style = CapButt,
        .join_style = JoinBevel
    };
    unsigned long valuemask = GCCapStyle | GCJoinStyle;
    
    gc = XCreateGC(display, win, valuemask, &values);
    if (gc < 0) {
        fprintf(stderr, "XCreateGC: \n");
    }

    XSetForeground(display, gc, white_pixel);
    XSetBackground(display, gc, black_pixel);
    XSetFillStyle(display, gc, FillSolid);
    XSetLineAttributes(display, gc, 2, LineSolid, CapRound, JoinRound);

    XDrawLine(display, win, gc, 20, 20, 40, 100);

    XMapWindow(display, win);

    XSync(display, False);

    sleep(4);
    XCloseDisplay(display);
}


