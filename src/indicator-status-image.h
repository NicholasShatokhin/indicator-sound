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

#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>

#ifndef __INDICATOR_STATUS_IMAGE_H__
#define __INDICATOR_STATUS_IMAGE_H__

G_BEGIN_DECLS

#define INDICATOR_STATUS_IMAGE_TYPE            (indicator_status_image_get_type ())
#define INDICATOR_STATUS_IMAGE(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), INDICATOR_STATUS_IMAGE_TYPE, IndicatorStatusImage))
#define INDICATOR_STATUS_IMAGE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), INDICATOR_STATUS_IMAGE_TYPE, IndicatorStatusImageClass))
#define IS_INDICATOR_STATUS_IMAGE(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), INDICATOR_STATUS_IMAGE_TYPE))
#define IS_INDICATOR_STATUS_IMAGE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), INDICATOR_STATUS_IMAGE_TYPE))
#define INDICATOR_STATUS_IMAGE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), INDICATOR_STATUS_IMAGE_TYPE, IndicatorStatusImageClass))

typedef struct _IndicatorStatusImage      IndicatorStatusImage;
typedef struct _IndicatorStatusImageClass IndicatorStatusImageClass;

struct _IndicatorStatusImageClass {
	GtkImageClass parent_class;
};

struct _IndicatorStatusImage {
	GtkImage parent;
    GdkWindow *GSEAL (event_window);
};

GType indicator_status_image_get_type (void);

IndicatorStatusImage* indicator_status_image_new(gchar* image_name);

G_END_DECLS

#endif

