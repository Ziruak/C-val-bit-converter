#include <gtk/gtk.h>
#include <string.h>
#include <stdint.h>
#include <float.h>
#include <stdlib.h>
#include <time.h>
#include "Converter.h"

typedef struct w_data {
    GtkRadioButton* rbs[7];
    GtkRadioButton* modes[3];
    GtkEntry* en_val, *en_mem, *en_out;
} gui_data;

int get_active_mode(gui_data *udata) {
    int res = 0;
    for (int i = 1; i < 3; ++i) {
        if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(udata->modes[i]))==TRUE)
            res = i;
    }
    return res;
}

int get_active_datatype(gui_data *udata) {
    int res = 0;
    for (int i = 1; i < 7; ++i) {
        if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(udata->rbs[i])))
            res = i;
    }
    return res;
}

void generate_val(GtkWidget *w, gpointer udata) {
    char str[128] = "";
    gui_data *data = udata;
    switch (get_active_datatype(data))
    {
    case 0:
        {
        char sym = rand() % (CHAR_MAX+1);
        str[0] = sym;
        str[1] = '\0';
        break;
        }
    case 1:
        {
        int num = INT32_MIN + rand()%INT32_MAX + rand()%INT32_MAX;
        snprintf(str, sizeof(str), "%d", num);
        break;
        }
    case 2:
        {
        unsigned int num = rand()%INT32_MAX + rand()%INT32_MAX;
        snprintf(str, sizeof(str), "%u", num);
        break;
        }
    case 3:
        {
        long num = LONG_MIN + ((long)rand()*((long)rand()%100)) * (-1 + rand()%2);
        snprintf(str, sizeof(str), "%ld", num);
        break;
        }
    case 4:
        {
        unsigned long num = ((long)rand()*(long)rand());
        snprintf(str, sizeof(str), "%lu", num);
        break;
        }
    case 5:
        {
        float num = (float)rand()/(float)rand();
        snprintf(str, sizeof(str), "%f", num);
        break;
        }
    case 6:
        {
        double num = (double)rand()/(double)(rand());
        snprintf(str, sizeof(str), "%lf", num);
        break;
        }
    default:
        break;
    }
    gtk_entry_set_text(GTK_ENTRY(data->en_val),str);
}

void convert_val_to_bytes(gui_data* data) {
    int type = get_active_datatype(data);
    int res = 0;
    const char* e_str = gtk_entry_get_text(data->en_val);
    char str[129];
    switch (type)
    {
    case 0:
        {
        char val;
        if((res = sscanf(e_str,"%c", &val)))
            convert_char_to_bytes(str,val);
        break;
        }
    case 1:
        {
        int val;
        if((res = sscanf(e_str,"%d", &val)))
            convert_int_to_bytes(str,val);
        break;
        }
    case 2:
        {
        unsigned int val;
        if((res = sscanf(e_str,"%u", &val)))
            convert_uint_to_bytes(str,val);
        break;
        }
    case 3:
        {
        long val;
        if((res = sscanf(e_str,"%ld", &val)))
            convert_long_to_bytes(str,val);
        break;
        }
    case 4:
        {
        unsigned long val;
        if((res = sscanf(e_str,"%lu", &val)))
            convert_ulong_to_bytes(str,val);
        break;
        }
    case 5:
        {
        float val;
        if((res = sscanf(e_str,"%f", &val)))
            convert_float_to_bytes(str,val);
        break;
        }
    case 6:
        {
        double val;
        if((res = sscanf(e_str,"%lf", &val)))
            convert_double_to_bytes(str,val);
        break;
        }
    default:
        break;
    }
    if (res) {
        gtk_entry_set_text(data->en_mem,str);
        gtk_entry_set_text(data->en_out, "Перевод успешен");
    }
    else {
        gtk_entry_set_text(data->en_out, "Неверный ввод");
    }
}

void convert_bytes_to_val(gui_data* data) {
    int type = get_active_datatype(data);
    int res = 0;
    const char* e_str = gtk_entry_get_text(data->en_mem);
    char str[129];
    switch (type)
    {
    case 0:
        {
        char val;
        res = convert_bytes_to_char(e_str,&val);
        if (res) snprintf(str,sizeof(str),"%c",val);
        break;
        }
    case 1:
        {
        int val;
        res = convert_bytes_to_int(e_str,&val);
        if (res) snprintf(str,sizeof(str),"%d",val);
        break;
        }
    case 2:
        {
        unsigned int val;
        res = convert_bytes_to_uint(e_str,&val);
        if (res) snprintf(str,sizeof(str),"%u",val);
        break;
        }
    case 3:
        {
        long val;
        res = convert_bytes_to_long(e_str,&val);
        if (res) snprintf(str,sizeof(str),"%ld",val);
        break;
        }
    case 4:
        {
        unsigned long val;
        res = convert_bytes_to_ulong(e_str,&val);
        if (res) snprintf(str,sizeof(str),"%lu",val);
        break;
        }
    case 5:
        {
        float val;
        res = convert_bytes_to_float(e_str,&val);
        if (res) snprintf(str,sizeof(str),"%f",val);
        break;
        }
    case 6:
        {
        double val;
        res = convert_bytes_to_double(e_str,&val);
        if (res) snprintf(str,sizeof(str),"%lf",val);
        break;
        }
    default:
        break;
    }
    if (res) {
        gtk_entry_set_text(data->en_val,str);
        gtk_entry_set_text(data->en_out, "Перевод успешен");
    }
    else {
        gtk_entry_set_text(data->en_out, "Неверный ввод");
    }
}

void test_value(gui_data* data) {
    int type = get_active_datatype(data);
    int res = 0;
    const char* e_str = gtk_entry_get_text(data->en_val);
    char str[129];
    switch (type)
    {
    case 0:
        {
        char val;
        if((res = sscanf(e_str,"%c", &val)))
            convert_char_to_bytes(str,val);
        break;
        }
    case 1:
        {
        int val;
        if((res = sscanf(e_str,"%d", &val)))
            convert_int_to_bytes(str,val);
        break;
        }
    case 2:
        {
        unsigned int val;
        if((res = sscanf(e_str,"%u", &val)))
            convert_uint_to_bytes(str,val);
        break;
        }
    case 3:
        {
        long val;
        if((res = sscanf(e_str,"%ld", &val)))
            convert_long_to_bytes(str,val);
        break;
        }
    case 4:
        {
        unsigned long val;
        if((res = sscanf(e_str,"%lu", &val)))
            convert_ulong_to_bytes(str,val);
        break;
        }
    case 5:
        {
        float val;
        if((res = sscanf(e_str,"%f", &val)))
            convert_float_to_bytes(str,val);
        break;
        }
    case 6:
        {
        double val;
        if((res = sscanf(e_str,"%lf", &val)))
            convert_double_to_bytes(str,val);
        break;
        }
    default:
        break;
    }
    if (res) {
        if (strcmp(str,gtk_entry_get_text(data->en_mem))==0)
            gtk_entry_set_text(data->en_out, "Верно");
        else
            gtk_entry_set_text(data->en_out, "Неверно");
    }
    else {
        gtk_entry_set_text(data->en_out, "Неверный ввод");
    }
}

void convert(GtkWidget *w, gpointer udata) {
    int mode = get_active_mode(udata);
    switch (mode)
    {
    case 0:
        convert_val_to_bytes(udata);
        break;
    case 1:
        convert_bytes_to_val(udata);
        break;
    case 2:
        test_value(udata);
        break;
    default:
        break;
    }
}

void mem_entry_text_handler(GtkEntry *entry, const gchar *text, gint length,
                             gint *position, gpointer data) {
  GtkEditable *editable = GTK_EDITABLE(entry);
  int count = 0;
  gchar *result = g_new(gchar, length);

  for (int i = 0; i < length; i++) {
    if (text[i] == '0' || text[i] == '1') {
      result[count++] = text[i];
    }
  }

  if (count > 0) {
    g_signal_handlers_block_by_func(G_OBJECT(editable),
                                    G_CALLBACK(mem_entry_text_handler), data);
    gtk_editable_insert_text(editable, result, count, position);
    g_signal_handlers_unblock_by_func(
        G_OBJECT(editable), G_CALLBACK(mem_entry_text_handler), data);
  }

  g_signal_stop_emission_by_name(G_OBJECT(editable), "insert_text");

  g_free(result);
}

void converter_exit(GtkWidget *window, gpointer *data) {
    free(data);
    gtk_main_quit();
}

int main(int argc, char *argv[]) {
    GtkWidget *window, *vbox;
    GtkWidget *label_value, *label_memory, *label_out, *label_help;
    GtkWidget *vbox_rbtns, *hbox, *vbox_othr, *hbox_modes;
    GtkWidget *rb_char, *rb_int, *rb_uint, *rb_long, *rb_ulong, *rb_float, *rb_double;
    GtkWidget *rb_mode_val_to_mem, *rb_mode_mem_to_val, *rb_mode_test;
    GtkWidget *entry_value, *entry_memory, *entry_out;
    GtkWidget *btn_convert, *btn_generate_val;
    gui_data *udata;

    gtk_init(&argc, &argv);  // initilizes gtk. Nust be called before other funcs

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);  // create window
    gtk_window_set_title(GTK_WINDOW(window), "Converter");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    gtk_window_set_position(GTK_WINDOW(window), GTK_POS_LEFT);
    gtk_container_set_border_width(GTK_CONTAINER(window), 5);

    udata = (gui_data*) malloc(sizeof(gui_data));
    srand(time(NULL));


    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    label_value = gtk_label_new("Значение:");
    gtk_box_pack_start(GTK_BOX(vbox), label_value, FALSE, FALSE, 0);

    entry_value = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), entry_value, FALSE, FALSE, 0);
    gtk_entry_set_max_length(GTK_ENTRY(entry_value), 129);

    label_memory = gtk_label_new("Представление в памяти:");
    gtk_box_pack_start(GTK_BOX(vbox), label_memory, FALSE, FALSE, 0);

    entry_memory = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), entry_memory, FALSE, FALSE, 0);
    gtk_entry_set_max_length(GTK_ENTRY(entry_memory), 129);
    g_signal_connect(entry_memory, "insert_text", G_CALLBACK(mem_entry_text_handler),NULL);

    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 0);

    vbox_rbtns = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(hbox), vbox_rbtns, TRUE, TRUE, 0);


    rb_char = gtk_radio_button_new_with_label(NULL,"char");
    rb_int = gtk_radio_button_new_with_label(NULL,"int");
    rb_uint = gtk_radio_button_new_with_label(NULL,"unsigned int");
    rb_long = gtk_radio_button_new_with_label(NULL,"long");
    rb_ulong = gtk_radio_button_new_with_label(NULL,"unsigned long");
    rb_float = gtk_radio_button_new_with_label(NULL,"float");
    rb_double = gtk_radio_button_new_with_label(NULL,"double");

    gtk_radio_button_join_group(GTK_RADIO_BUTTON(rb_int),GTK_RADIO_BUTTON(rb_char));
    gtk_radio_button_join_group(GTK_RADIO_BUTTON(rb_uint),GTK_RADIO_BUTTON(rb_char));
    gtk_radio_button_join_group(GTK_RADIO_BUTTON(rb_long),GTK_RADIO_BUTTON(rb_char));
    gtk_radio_button_join_group(GTK_RADIO_BUTTON(rb_ulong),GTK_RADIO_BUTTON(rb_char));
    gtk_radio_button_join_group(GTK_RADIO_BUTTON(rb_float),GTK_RADIO_BUTTON(rb_char));
    gtk_radio_button_join_group(GTK_RADIO_BUTTON(rb_double),GTK_RADIO_BUTTON(rb_char));
   
    gtk_box_pack_start(GTK_BOX(vbox_rbtns), rb_char, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox_rbtns), rb_int, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox_rbtns), rb_uint, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox_rbtns), rb_long, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox_rbtns), rb_ulong, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox_rbtns), rb_float, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox_rbtns), rb_double, TRUE, TRUE, 0);

    vbox_othr = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_pack_start(GTK_BOX(hbox), vbox_othr, TRUE, TRUE, 0);


    btn_convert = gtk_button_new_with_label("Перевести");
    gtk_box_pack_start(GTK_BOX(vbox_othr), btn_convert, FALSE, TRUE, 5);

    btn_generate_val = gtk_button_new_with_label("Сгенерировать значение");
    gtk_box_pack_start(GTK_BOX(vbox_othr), btn_generate_val, FALSE, TRUE, 5);

    hbox_modes = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(vbox_othr), hbox_modes, FALSE, TRUE, 5);

    rb_mode_val_to_mem = gtk_radio_button_new_with_label(NULL,"Значение в представление в памяти");
    rb_mode_mem_to_val = gtk_radio_button_new_with_label(NULL,"Представление в памяти в значение");
    rb_mode_test = gtk_radio_button_new_with_label(NULL,"Тестовый режим");

    gtk_radio_button_join_group(GTK_RADIO_BUTTON(rb_mode_mem_to_val),GTK_RADIO_BUTTON(rb_mode_val_to_mem));
    gtk_radio_button_join_group(GTK_RADIO_BUTTON(rb_mode_test),GTK_RADIO_BUTTON(rb_mode_val_to_mem));

    gtk_box_pack_start(GTK_BOX(hbox_modes), rb_mode_val_to_mem, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_modes), rb_mode_mem_to_val, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_modes), rb_mode_test, TRUE, TRUE, 0);

    label_out = gtk_label_new("Сообщение:");
    gtk_box_pack_start(GTK_BOX(vbox_othr), label_out, FALSE, TRUE, 5);

    entry_out = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox_othr), entry_out, FALSE, TRUE, 5);

    label_help = gtk_label_new("Инструкция:\n"
    "[1]: Выберите один из трех режимов.\n"
    "[2]: Выберите, с каким типом данных будет работать программа.\n"
    "[3]: Введите значение или сгенерируйте его с помощью кнопки.\n"
    "[4]: Используйте кнопку \"Перевести\".\n\n"
    "Инструкция к тестовому режиму:\n"
    "[1]: Введите или сгенерируйте значение.\n"
    "[2]: Введите предролагаемое представление в памяти.\n"
    "[3]: Нажмите кнопку \"Перевести\", чтобы увидеть правильность предположения.");
    gtk_box_pack_start(GTK_BOX(vbox_othr), label_help, TRUE, TRUE, 0);

    udata->rbs[0] = GTK_RADIO_BUTTON(rb_char) ; 
    udata->rbs[1] = GTK_RADIO_BUTTON(rb_int) ;
    udata->rbs[2] = GTK_RADIO_BUTTON(rb_uint) ;
    udata->rbs[3] = GTK_RADIO_BUTTON(rb_long) ;
    udata->rbs[4] = GTK_RADIO_BUTTON(rb_ulong) ;
    udata->rbs[5] = GTK_RADIO_BUTTON(rb_float) ;
    udata->rbs[6] = GTK_RADIO_BUTTON(rb_double) ;

    udata->modes[0] = GTK_RADIO_BUTTON(rb_mode_val_to_mem);
    udata->modes[1] = GTK_RADIO_BUTTON(rb_mode_mem_to_val);
    udata->modes[2] = GTK_RADIO_BUTTON(rb_mode_test);

    udata->en_out = GTK_ENTRY(entry_out);
    udata->en_mem = GTK_ENTRY(entry_memory);
    udata->en_val = GTK_ENTRY(entry_value);

    g_signal_connect(G_OBJECT(btn_generate_val), "clicked", G_CALLBACK(generate_val), udata);
    g_signal_connect(G_OBJECT(btn_convert), "clicked", G_CALLBACK(convert), udata);


    gtk_widget_add_events(window, GDK_KEY_PRESS_MASK);  // enable key press handler

    g_signal_connect(window, "destroy", G_CALLBACK(converter_exit), udata);  // on window destroy

    gtk_widget_show_all(window);  // show window and all of its children

    gtk_main();  // pass handler to gtk
    return 0;
}