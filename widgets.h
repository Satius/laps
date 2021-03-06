#include <X11/Xlib.h>

struct list_entry;

struct context
{
  Display* display;
  int screen;
  Window root;
  Window window;
  GC gc;
};

struct command_arg
{
  char* name;
  char* description;
  char* value;
};

char* arg_value(struct command_arg*, int, const char*);

struct notifier
{
  int fd;
  void* data;
  void (*callback)(int, void*);
};

struct widget_desc
{
  int args_count;
  struct command_arg* arguments;
  void (*on_init)(struct context*, struct list_entry** notiriers);
  Pixmap (*on_refresh)();
  void (*on_activate)();
  void (*on_del)(struct context*);
  int x, y;
  int w, h;
};

typedef void (*widget_callback)(struct widget_desc*, void*);

void add_widget(struct widget_desc* description);
void for_each_widget(widget_callback, void*);
int measure_widgets();
void init_widgets(struct context* context, struct list_entry** notifiers);
void notifiers_widgets(struct list_entry**);
void refresh_widgets(struct context* context);
void activate_widgets(int x, int y);
