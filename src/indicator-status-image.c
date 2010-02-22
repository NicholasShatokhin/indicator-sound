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
    gchar* a_little_secret;
};

#define INDICATOR_STATUS_IMAGE_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), INDICATOR_STATUS_IMAGE_TYPE, IndicatorStatusImagePrivate))

/* Prototypes */
static void indicator_status_image_class_init (IndicatorStatusImageClass *klass);
static void indicator_status_image_init       (IndicatorStatusImage *self);
static void indicator_status_image_dispose    (GObject *object);
static void indicator_status_image_finalize   (GObject *object); 

G_DEFINE_TYPE (IndicatorStatusImage, indicator_status_image, GTK_TYPE_IMAGE);

static void indicator_status_image_realize (GtkWidget *widget);
static void indicator_status_image_unrealize (GtkWidget *widget);
static void indicator_status_image_map (GtkWidget *widget);
static void indicator_status_image_unmap (GtkWidget *widget);

static gboolean indicator_status_image_scroll(GtkWidget  *widget, GdkEventScroll *event);

/* Listen to our scroll events */
/*static gboolean scroll_event_title_cb(GtkWidget *widget,  GdkEventScroll *event, gpointer  user_data);*/

static void indicator_status_image_class_init (IndicatorStatusImageClass *klass)
{
    GtkWidgetClass *widget_class;

	GObjectClass *object_class = G_OBJECT_CLASS (klass);
    widget_class = (GtkWidgetClass*) klass;

	g_type_class_add_private (klass, sizeof (IndicatorStatusImagePrivate));

	object_class->dispose = indicator_status_image_dispose;
	object_class->finalize = indicator_status_image_finalize;

    widget_class->realize = indicator_status_image_realize;
    widget_class->unrealize = indicator_status_image_unrealize;
    widget_class->map = indicator_status_image_map;
    widget_class->unmap = indicator_status_image_unmap;
    widget_class->scroll_event = indicator_status_image_scroll;

	return;
}


static void indicator_status_image_init (IndicatorStatusImage *self)
{
	g_debug("Building new Indicator Status Image");

    //g_signal_connect(self, "scroll-event", G_CALLBACK(scroll_event_title_cb), NULL);         

	return;
}


static void indicator_status_image_dispose (GObject *object)
{
	G_OBJECT_CLASS (indicator_status_image_parent_class)->dispose (object);
    
	return;
}

static void indicator_status_image_finalize (GObject *object)
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

static void indicator_status_image_realize (GtkWidget *widget)
{
    IndicatorStatusImage *status_image;
    GdkWindowAttr attributes;
    gint attributes_mask;

    status_image = INDICATOR_STATUS_IMAGE(widget);
    GTK_WIDGET_SET_FLAGS (widget, GTK_REALIZED);

    attributes.window_type = GDK_WINDOW_CHILD;
    attributes.x = widget->allocation.x;
    attributes.y = widget->allocation.y;
    attributes.width = widget->allocation.width;
    attributes.height = widget->allocation.height;
    attributes.wclass = GDK_INPUT_ONLY;
    attributes.event_mask = gtk_widget_get_events (widget);
    attributes.event_mask |= GDK_SCROLL_MASK;

    attributes_mask = GDK_WA_X | GDK_WA_Y;

    widget->window = gtk_widget_get_parent_window (widget);
    g_object_ref (widget->window);

    status_image->event_window = gdk_window_new (gtk_widget_get_parent_window (widget),
				     &attributes, attributes_mask);
    gdk_window_set_user_data (status_image->event_window, status_image);
    widget->style = gtk_style_attach (widget->style, widget->window);
}

static void indicator_status_image_unrealize (GtkWidget *widget)
{
    IndicatorStatusImage *status_image =  INDICATOR_STATUS_IMAGE(widget);

    if(status_image->event_window)
    {
        gdk_window_set_user_data(status_image->event_window, NULL);
        gdk_window_destroy(status_image->event_window);
        status_image->event_window = NULL;
    }
    GTK_WIDGET_CLASS (indicator_status_image_parent_class)->unrealize (widget);
}

static void indicator_status_image_map (GtkWidget *widget)
{
  IndicatorStatusImage *status_image =  INDICATOR_STATUS_IMAGE(widget);
 
  GTK_WIDGET_CLASS (indicator_status_image_parent_class)->map (widget);

  if (status_image->event_window)
    gdk_window_show (status_image->event_window);
}

static void indicator_status_image_unmap (GtkWidget *widget)
{
  IndicatorStatusImage *status_image =  INDICATOR_STATUS_IMAGE(widget);
    
  if (status_image->event_window)
    gdk_window_hide (status_image->event_window);

  GTK_WIDGET_CLASS (indicator_status_image_parent_class)->unmap (widget);
}

static gboolean indicator_status_image_scroll(GtkWidget  *widget, GdkEventScroll *event)
{
    IndicatorStatusImage *status_image;
    g_debug("in the indicator_status_image");
    if (event->type == GDK_SCROLL){
        status_image = INDICATOR_STATUS_IMAGE(widget);
    /*  if (status_image->focus_on_click && !GTK_WIDGET_HAS_FOCUS (widget))*/
    /*	gtk_widget_grab_focus (widget);*/
        g_signal_emit_by_name(status_image, "scroll-event", event);
        return TRUE;
    }
    return FALSE;
}



/*static gboolean scroll_event_title_cb(GtkWidget *widget, GdkEventScroll *event, gpointer user_data)*/
/*{*/
/*    g_debug("scroll event call back");*/
/*    return FALSE;*/
/*}*/


