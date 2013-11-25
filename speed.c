/*
  wondershaper gui
  
  Copyright 2013 diplay <diplaysuper@gmail.com>
  
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
  MA 02110-1301, USA.
  
  
*/


#include "speed.h"

GtkWidget * txtDown, * txtUp;
GtkWidget * cmbAdapters;
GList * adapters = NULL;

char * locale_from_utf8(const char * str)
{
	gchar * locale_str;
	gsize bytes_written = 0;
	GError * err = NULL;

	locale_str = g_locale_from_utf8(str, -1, NULL, &bytes_written, &err);
	if (err)
	{
		g_warning("g_locale_from_utf8 failed: %s", err->message);
		g_error_free(err);
	}

	return locale_str;
}

int get_adapters()
{
	struct if_nameindex * a, * i;
	a = if_nameindex();
	if(a == NULL)
		return 1;
	for(i = a; !(i->if_index == 0 && i->if_name == NULL); i++)
		adapters = g_list_prepend(adapters, locale_from_utf8(i->if_name));
	if_freenameindex(a);
	return 0;
}

void clear_speed(GtkWidget * widget, gpointer data)
{
	g_print("sudo wondershaper eth0 clear");
	system("sudo wondershaper eth0 clear");
}

void set_speed(GtkWidget * widget, gpointer data)
{
	const char * a = gtk_entry_get_text(GTK_ENTRY(GTK_COMBO(cmbAdapters)->entry));
	const char * d = gtk_entry_get_text(GTK_ENTRY(txtDown));
	const char * u = gtk_entry_get_text(GTK_ENTRY(txtUp));
	char str[256];
	sprintf(str, "%s %s %s %s", "sudo wondershaper", a, d, u);
	g_print("%s\n",str);
	system(str);
}

gboolean delete_event(GtkWidget * widget, GdkEvent  * event, gpointer data)
{
	return FALSE;
}

void destroy(GtkWidget * widget, gpointer data)
{
	gtk_main_quit();
}

void init_interface()
{
	GtkWidget * window;
	GtkWidget * btnSet, * btnClear;
	GtkWidget * hBox, * hBox2, * vBox;
	GtkWidget * lblDown, * lblUp;

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	g_signal_connect(window, "delete-event", G_CALLBACK(delete_event), NULL);
	g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window), 5);
	gtk_window_set_title(GTK_WINDOW(window), strings[TITLE]);

	txtDown = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(txtDown), strings[INITIAL_DOWN]);

	txtUp = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(txtUp), strings[INITIAL_UP]);

	lblDown = gtk_label_new(strings[TEXT_DOWN]);

	lblUp = gtk_label_new(strings[TEXT_UP]);

	btnSet = gtk_button_new_with_label(strings[SET_SPEED]);
	g_signal_connect(btnSet, "clicked", G_CALLBACK(set_speed), NULL);

	btnClear = gtk_button_new_with_label(strings[CLEAR]);
	g_signal_connect(btnClear, "clicked", G_CALLBACK(clear_speed), NULL);

	cmbAdapters = gtk_combo_new();
	gtk_combo_set_popdown_strings(GTK_COMBO(cmbAdapters), adapters);

	hBox = gtk_hbox_new(TRUE, 10);
	gtk_container_add(GTK_CONTAINER(hBox), txtDown);
	gtk_container_add(GTK_CONTAINER(hBox), txtUp);

	hBox2 = gtk_hbox_new(TRUE, 10);
	gtk_container_add(GTK_CONTAINER(hBox2), lblDown);
	gtk_container_add(GTK_CONTAINER(hBox2), lblUp);

	vBox = gtk_vbox_new(FALSE, 5);
	gtk_container_add(GTK_CONTAINER(vBox), cmbAdapters);
	gtk_container_add(GTK_CONTAINER(vBox), hBox2);
	gtk_container_add(GTK_CONTAINER(vBox), hBox);
	gtk_container_add(GTK_CONTAINER(vBox), btnSet);
	gtk_container_add(GTK_CONTAINER(vBox), btnClear);

	gtk_container_add(GTK_CONTAINER(window), vBox);

	gtk_widget_show(cmbAdapters);
	gtk_widget_show(txtDown);
	gtk_widget_show(txtUp);
	gtk_widget_show(lblUp);
	gtk_widget_show(lblDown);
	gtk_widget_show(hBox2);
	gtk_widget_show(hBox);
	gtk_widget_show(vBox);
	gtk_widget_show(btnSet);
	gtk_widget_show(btnClear);
	gtk_widget_show(window);
}

int main(int argc, char ** argv)
{
	gtk_init(&argc, &argv);
	if(get_adapters())
		adapters = g_list_append(adapters, (gpointer)strings[ADAPTERS_FAIL]);
	init_interface();
	gtk_main();
	return 0;
}

