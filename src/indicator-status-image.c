/*
Copyright 2010 Canonical Ltd.

Authors:
    Conor Curran <conor.curran@canonical.com>

This program is free software: you can redistribute it and/or modify it 
under the terms of the GNU General Public License version 3, as published 
by the Free Software Foundation.

This program is distributed in the hope that it will be useful, but 
WITHOUT ANY WARRANTY; without even the implied warranties of 
MERCHANTABILITY, SATISFACTORY QUALITY, or FITNESS FOR A PARTICULAR 
PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along 
with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "indicator-status-image.h"

typedef struct _IndicatorStatusImagePrivate IndicatorStatusImagePrivate;

struct _IndicatorStatusImagePrivate
{
    // GDK stuff for window
};

#define INDICATOR_STATUS_IMAGE_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), INDICATOR_STATUS_IMAGE_TYPE, IndicatorStatusImagePrivate))


/* Prototypes */
static void indicator_status_image_class_init (IndicatorStatusImageClass *klass);
static void indicator_status_image_init       (IndicatorStatusImage *self);
static void indicator_status_image_dispose    (GObject *object);
static void indicator_status_image_finalize   (GObject *object);

G_DEFINE_TYPE (IndicatorStatusImage, indicator_status_image, GTK_TYPE_IMAGE);

/* Listen to our scroll events */
/*static gboolean scroll_event_title_cb(GtkWidget *widget,  GdkEventScroll *event, gpointer  user_data);*/


static void indicator_status_image_class_init (IndicatorStatusImageClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);

	g_type_class_add_private (klass, sizeof (IndicatorStatusImagePrivate));

	object_class->dispose = indicator_status_image_dispose;
	object_class->finalize = indicator_status_image_finalize;

	return;
}

static void indicator_status_image_init (IndicatorStatusImage *self)
{
	g_debug("Building new Indicator Status Image");
	return;
}

static void indicator_status_image_dispose (GObject *object)
{
	G_OBJECT_CLASS (indicator_status_image_parent_class)->dispose (object);
	return;
}

static void
indicator_status_image_finalize (GObject *object)
{
	G_OBJECT_CLASS (indicator_status_image_parent_class)->finalize (object);
}

IndicatorStatusImage* indicator_status_image_new(gchar* image_name)
{
	//speaker_image = GTK_IMAGE(gtk_image_new_from_icon_name(current_name, GTK_ICON_SIZE_MENU));
    g_debug("about to set the image from name");

	IndicatorStatusImage *self = g_object_new(INDICATOR_STATUS_IMAGE_TYPE, NULL);
    g_debug("about to set the image from name");
    gtk_image_set_from_icon_name(GTK_IMAGE(self), image_name, GTK_ICON_SIZE_MENU);
    g_debug("after setting the image from name");

    return self;
}

/*static gboolean scroll_event_title_cb(GtkWidget *widget, GdkEventScroll *event, gpointer user_data)*/
/*{*/
/*    g_debug("scroll event call back");*/
/*    return FALSE;*/
/*}*/


