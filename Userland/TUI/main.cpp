/*
* Copyright (c) 2024, Patrick Wilmes <p.wilmes89@gmail.com>
* All rights reserved.
*
* SPDX-License-Identifier: BSD-2-Clause
*/
#include <ncurses.h>
#include <string.h>
#include <ctype.h>
#include <Forgebase.h>

#define NUM_BUTTONS 2

void draw_buttons(WINDOW *win, int selected);
void draw_list(WINDOW *win, int start, int num_items);

int main() {
    // Initialize ncurses
    initscr();
    cbreak();             // Disable line buffering
    noecho();             // Don't echo input
    keypad(stdscr, TRUE); // Enable special keys like arrows
    curs_set(1);          // Set the cursor visible for input field
    timeout(0);           // Non-blocking input check
    
    // Optional: Enable color if supported
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_WHITE, COLOR_BLUE);  // Buttons color
        init_pair(2, COLOR_BLACK, COLOR_WHITE); // Input bar color
        init_pair(3, COLOR_WHITE, COLOR_BLACK); // List color
        init_pair(4, COLOR_RED, COLOR_BLACK);   // Highlighted list item
    }

    // Get terminal size
    int height, width;
    getmaxyx(stdscr, height, width);

    // Define window heights
    int button_height = 3;      // Enough for two rows of buttons
    int input_height = 3;       // Single line for input bar
    int list_height = height - button_height - input_height;

    // Create windows
    WINDOW *button_win = newwin(button_height, width, 0, 0);
    WINDOW *input_win = newwin(input_height, width, button_height, 0);
    WINDOW *list_win = newwin(list_height, width, button_height + input_height, 0);

    // Refresh the main window to ensure the ncurses state is properly updated
    refresh();

    // Variables for state tracking
    char input[100] = {0}; // Input buffer
    int selected_button = 0; // Track the selected button
    int input_focus = 1;    // 0 = buttons, 1 = input field, 2 = list
    int list_offset = 0;    // Start index for the list
    int list_selection = 0; // Currently selected item in list

    // Draw initial layout
    draw_buttons(button_win, selected_button);
    box(input_win, 0, 0);
    wrefresh(input_win);
    draw_list(list_win, list_offset, list_height - 2);
    
    // Main loop to capture user input
    int ch;
    Core::Forgebase forgebase;
    while ((ch = getch()) != 'q') {
        switch (input_focus) {
            case 0: // Button focus
                if (ch == KEY_LEFT && selected_button > 0) {
                    selected_button--;
                    draw_buttons(button_win, selected_button);
                } else if (ch == KEY_RIGHT && selected_button < NUM_BUTTONS - 1) {
                    selected_button++;
                    draw_buttons(button_win, selected_button);
                } else if (ch == '\n') {
                    // Handle button press (e.g., Button 1 or Button 2 pressed)
                    if (selected_button == 1) {
                        forgebase.index();
                    }
                    mvprintw(height - 2, 1, "Button %d pressed", selected_button + 1);
                    refresh();
                } else if (ch == KEY_DOWN) {
                    input_focus = 1; // Move focus to input field
                    curs_set(1);     // Show cursor for input field
                }
                break;
            case 1: // Input focus
                if (ch == KEY_UP) {
                    input_focus = 0; // Go back to buttons
                    curs_set(0);     // Hide cursor
                } else if (ch == KEY_DOWN) {
                    input_focus = 2; // Move to list
                    curs_set(0);     // Hide cursor
                } else if (ch == '\n') {
                    // Input submitted, handle it
                    mvprintw(height - 3, 1, "Input: %s", input);
                    memset(input, 0, sizeof(input)); // Clear input
                } else if (ch == KEY_BACKSPACE || ch == 127) {
                    // Handle backspace
                    int len = strlen(input);
                    if (len > 0) {
                        input[len - 1] = '\0';
                    }
                } else if (isprint(ch)) {
                    // Add input to buffer
                    int len = strlen(input);
                    if (len < sizeof(input) - 1) {
                        input[len] = ch;
                        input[len + 1] = '\0';
                    }
                }
                
                // Clear and redraw input bar
                werase(input_win);
                box(input_win, 0, 0);
                mvwprintw(input_win, 1, 1, "Input: %s", input);
                wrefresh(input_win);
                break;
            case 2: // List focus
                if (ch == KEY_UP && list_selection > 0) {
                    list_selection--;
                    draw_list(list_win, list_offset, list_height - 2);
                } else if (ch == KEY_DOWN && list_selection < list_height - 3) {
                    list_selection++;
                    draw_list(list_win, list_offset, list_height - 2);
                } else if (ch == '\n') {
                    // Handle list item selection
                    mvprintw(height - 2, 1, "Item %d selected", list_selection + 1);
                    refresh();
                }
                break;
        }

        // Refresh windows
        wrefresh(button_win);
        wrefresh(input_win);
        wrefresh(list_win);
    }

    // Cleanup
    delwin(button_win);
    delwin(input_win);
    delwin(list_win);
    endwin(); // End ncurses
    return 0;
}

// Draw buttons and handle selection
void draw_buttons(WINDOW *win, int selected) {
    werase(win);
    wbkgd(win, COLOR_PAIR(1));
    mvwprintw(win, 1, 2, "[Reindex]");
    mvwprintw(win, 1, 15, "[Don't touch]");

    if (selected == 0) {
        wattron(win, A_REVERSE);
        mvwprintw(win, 1, 2, "[Reindex]");
        wattroff(win, A_REVERSE);
    } else if (selected == 1) {
        wattron(win, A_REVERSE);
        mvwprintw(win, 1, 15, "[Don't touch]");
        wattroff(win, A_REVERSE);
    }
    box(win, 0, 0);
    wrefresh(win);
}

// Draw list with highlighting for selection
void draw_list(WINDOW *win, int start, int num_items) {
    werase(win);
    box(win, 0, 0);

    for (int i = 0; i < num_items; i++) {
        if (i == start) {
            wattron(win, A_REVERSE);
        }
        mvwprintw(win, i + 1, 2, "Item %d", i + 1);
        wattroff(win, A_REVERSE);
    }
    wrefresh(win);
}

