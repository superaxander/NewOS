#include "kernel/lib/fallback_vga.h"
/* Hardware text mode color constants. */
;
 
uint8_t make_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}
 
uint16_t make_vgaentry(char c, uint8_t color)
{
	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}
 
static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;
 
void terminal_initialize()
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
		}
	}
}

void move_cursor_auto()
{
	move_cursor(terminal_column, terminal_row);
}

void move_cursor(size_t x, size_t y)
{
    unsigned temp;

    temp = y * 80 + x;

    outportb(0x3D4, 14);
    outportb(0x3D5, temp >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, temp);
}

void terminal_translate(int x, int y)
{
	int x_new, y_new;
	x_new = terminal_column + x;
	y_new = terminal_row    + y;
	terminal_column = x_new < (int)VGA_WIDTH  ? (x_new < 0 ? 0 : x_new) : (VGA_WIDTH  - 1);
	terminal_row    = y_new < (int)VGA_HEIGHT ? (y_new < 0 ? 0 : y_new) : (VGA_HEIGHT - 1);
}

void terminal_set_location(size_t x, size_t y)
{
	terminal_column = x < (int)VGA_WIDTH  ? x : (VGA_WIDTH  - 1);
	terminal_row    = y < (int)VGA_HEIGHT ? y : (VGA_HEIGHT - 1);
}
 
void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = make_vgaentry(c, color);
}

/**
 * terminal_scroll()
 *
 * Returns: 1 if succesfull or 0 if not
 */

int terminal_scroll()
{
	uint16_t new_buffer[VGA_HEIGHT * VGA_WIDTH];

	for (int y = VGA_HEIGHT - 1; y > 0; y--) 
	{
		for (int x = VGA_WIDTH -1; x >= 0; x--)
		{
			if((y - 1) < 0)
				return 0;
			new_buffer[(y - 1) * VGA_WIDTH + x] = terminal_buffer[y * VGA_WIDTH + x];
		}
	}
	for (size_t x = 0; x < VGA_WIDTH; x++)
		new_buffer[(VGA_HEIGHT-1) * VGA_WIDTH + x] = make_vgaentry(' ', terminal_color);
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = new_buffer[index];
		}
	}
}
 
void terminal_putchar(char c)
{
	if (c == '\n')
	{
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT) {
			terminal_scroll(1);
			terminal_row = VGA_HEIGHT-1;
		}
		move_cursor_auto();
		return;
	}
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT) {
			terminal_scroll(1);
			terminal_row = VGA_HEIGHT-1;
		}
	}
	move_cursor_auto();
}
 
void terminal_writestring(const char* data)
{
	size_t datalen = strlen(data);
	for (size_t i = 0; i < datalen; i++)
		terminal_putchar(data[i]);
}
