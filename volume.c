#include "utils.h"
#include "widgets.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "resources/volume.xbm"

// libs: alsa

Pixmap volume;

static struct command_arg args[] =
{
  { "volctl", "Use the specified file as a volume control","/dev/snd/controlC0" },
  { "volact", "Call the specified binary when volume widget activated", "talsamixer" }
};

static void on_init(struct context* context, struct list_entry** notifiers)
{
  volume = img_init(volume);
}

static Pixmap on_refresh()
{
  return volume;
}

static void on_activate()
{
  detach(arg_value(args, alen(args), "volact"));
}

static void on_del(struct context* context)
{
}

/////////////////// Initialization code ///////////////////

static void __attribute__ ((constructor)) init()
{
  static struct widget_desc description =
  {
    alen(args),
    args,
    &on_init,
    &on_refresh,
    &on_activate,
    &on_del
  };

  add_widget(&description);
}
