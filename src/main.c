#define GL_GLEXT_PROTOTYPES why

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<stdint.h>

#include <glib-2.0/glib.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include "shaders.h"

const int WIN_WIDTH  = 1920;
const int WIN_HEIGHT = 1080;

GLuint vao;
GLuint p;

static gboolean render(GtkGLArea *area, GdkGLContext *ctx)
{
    (void)area;
    (void)ctx;

    glUseProgram(p);
    glBindVertexArray(vao);
    glVertexAttrib1f(0, 0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    return TRUE;
}

static void realize(GtkGLArea *area)
{
    gtk_gl_area_make_current(area);

    GLuint f = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(f, 1, &raymarch_f, NULL);
    glCompileShader(f);

    GLint error = 0;
    glGetShaderiv(f, GL_COMPILE_STATUS, &error);
    if(error == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(f, GL_INFO_LOG_LENGTH, &maxLength);

        char* error = malloc(maxLength);
        glGetShaderInfoLog(f, maxLength, &maxLength, error);
        printf("%s\n", error);

        exit(1);
    }

    GLuint v = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(v, 1, &raymarch_v, NULL);
    glCompileShader(v);

    glGetShaderiv(v, GL_COMPILE_STATUS, &error);
    if(error == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(v, GL_INFO_LOG_LENGTH, &maxLength);

        char* error = malloc(maxLength);
        glGetShaderInfoLog(v, maxLength, &maxLength, error);
        printf("%s\n", error);

        exit(1);
    }

    p = glCreateProgram();
    glAttachShader(p,v);
    glAttachShader(p,f);
    glLinkProgram(p);

    glGetProgramiv(p, GL_LINK_STATUS, (int *)&error);
    if (error == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(p, GL_INFO_LOG_LENGTH, &maxLength);

        char* error = malloc(maxLength);
        glGetProgramInfoLog(p, maxLength, &maxLength,error);
        printf("%s\n", error);

        exit(1);
    }

    glGenVertexArrays(1, &vao);

    GdkGLContext *context = gtk_gl_area_get_context(area);
    GdkWindow *glwindow = gdk_gl_context_get_window(context);
    GdkFrameClock *frame_clock = gdk_window_get_frame_clock(glwindow);

    g_signal_connect_swapped(frame_clock, "update", G_CALLBACK(gtk_gl_area_queue_render), area);

    gdk_frame_clock_begin_updating(frame_clock);
}

int main(int argc, char **argv) {
    gtk_init(&argc, &argv);

    GtkWidget *win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    GtkWidget *glarea = gtk_gl_area_new();
    gtk_container_add(GTK_CONTAINER(win), glarea);

    g_signal_connect(win, "destroy", gtk_main_quit, NULL);
    g_signal_connect(glarea, "realize", G_CALLBACK(realize), NULL);
    g_signal_connect(glarea, "render", G_CALLBACK(render), NULL);

    gtk_widget_show_all (win);

    gtk_window_set_title((GtkWindow*)win, "Demo");
    gtk_window_resize((GtkWindow*)win, WIN_WIDTH, WIN_HEIGHT);
    gtk_window_fullscreen((GtkWindow*)win);
    GdkWindow* window = gtk_widget_get_window(win);
    GdkDisplay* disp = gdk_window_get_display(window);
    GdkCursor* cursor = gdk_cursor_new_for_display(disp, GDK_BLANK_CURSOR);
    gdk_window_set_cursor(window, cursor);

    gtk_main();

    return 0;
}

