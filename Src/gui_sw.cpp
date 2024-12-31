#include "gui_sw.h"

static uint8_t const bmp_switch8[][12] = 
{
	{
		0x1C,0x22,0x49,0x5D,0x5D,0x49,0x41,0x41,0x41,0x41,0x22,0x1C			//Off
	},
	{
		0x1C,0x22,0x49,0x5D,0x5D,0x55,0x49,0x5D,0x5D,0x49,0x22,0x1C			//On
	}
};
static uint8_t const bmp_switch24x15[][64] =
{
	{
		0xff, 0x01, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xff, 0x7f, 0x40, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 
		0x5f, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x7f,

	},
	{	
		0xff, 0x01, 0xa9, 0x55, 0xa9, 0x55, 0xa9, 0x55, 0xa9, 0x55, 0xa9, 0x55, 0xa9, 0x55, 0x01, 0xfd, 
		0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0x01, 0xff, 0x7f, 0x40, 0x4a, 0x55, 0x4a, 0x55, 0x4a, 0x55, 
		0x4a, 0x55, 0x4a, 0x55, 0x4a, 0x55, 0x40, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x40, 0x7f	
	}
};


void gui_sw::create(int16_t x, int16_t y, uint8_t size, gui_state state)
{
    this->deinit();
	this->set_window(&window_screen_size);
    this->add_state(state);
    this->set_x(x);
    this->set_y(y);
    switch (size)
    {
    case SW_SIZE_1:
        /* code */
        this->set_feature((void *)bmp_switch8[this->check_state(GUI_STATE_CHECKED)]);
		this->set_w(12);
		this->set_h(8);
        break;
    case SW_SIZE_2:
        /* code */
        this->set_feature((void *)bmp_switch24x15[this->check_state(GUI_STATE_CHECKED)]);
        this->set_w(24);
		this->set_h(15);
        break;
    }
	gui_obj::gui_obj_add_head(dynamic_cast<gui_obj*>(this));
}
void gui_sw::toggle()
{
    if(this->check_state(GUI_STATE_CHECKED)) this->clear_state(GUI_STATE_CHECKED);
    else this->add_state(GUI_STATE_CHECKED);
}
void gui_sw::draw()
{
	if(this->get_h() > 8) this->set_feature((void *)bmp_switch24x15[this->check_state(GUI_STATE_CHECKED)]);
	else this->set_feature((void *)bmp_switch8[this->check_state(GUI_STATE_CHECKED)]);
	gui_window_draw_bmp(this->get_window(), this->get_x(), this->get_y(), this->get_w(), this->get_h(), (uint8_t *)this->get_feature(), DRAW_STATE_ON);
	//gui_window_draw_str(this->get_window(), this->get_x() - 10, this->get_y() + 20, "123456789", DRAW_STATE_ON);	
}