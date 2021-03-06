/*
 * This algorithm was created special for the template "tiles.png".
 * Modify it as you need (including the resolution) and freely use
 * with this algorithm.
 */

#pragma once

#include "engine.hxx"
#include "global_data.h"

constexpr int default_tileset = 1, default_frame = 1;

void autotile(
    int** map_grid /*2d map. 1 - wall, 0 - ground*/,
    CHL::instance*** grid /*2D map of CHL::instance*'s and nullptr's*/,
    int x_size,
    int y_size) {
    for (int y = 0; y < y_size; y++) {
        for (int x = 0; x < x_size; x++) {
            bool left_bonds = x - 1 >= 0;
            bool right_bonds = x + 1 < x_size;
            bool top_bonds = y - 1 >= 0;
            bool bot_bonds = y + 1 < y_size;
            if (map_grid[y][x] == 0) {
                bool top = top_bonds && (map_grid[y - 1][x] == 1);
                bool bottom = bot_bonds && (map_grid[y + 1][x] == 1);
                bool left = left_bonds && (map_grid[y][x - 1] == 1);
                bool right = right_bonds && (map_grid[y][x + 1] == 1);
                if (top &&
                    grid[y - 1][x]->selected_tileset == default_tileset &&
                    grid[y - 1][x]->selected_frame == default_frame) {
                    if (left_bonds && right_bonds &&
                        map_grid[y - 1][x - 1] == 0 &&
                        map_grid[y - 1][x + 1] == 0) {
                        grid[y - 1][x]->selected_tileset = 0;
                        grid[y - 1][x]->selected_frame = 5;
                    } else {
                        grid[y - 1][x]->selected_tileset = 0;
                        grid[y - 1][x]->selected_frame = 1;
                    }
                }
                if (top) {
                    if (left_bonds && map_grid[y - 1][x - 1] == 0) {
                        grid[y - 1][x]->selected_tileset = 0;
                        grid[y - 1][x]->selected_frame = 0;
                    } else if (right_bonds && map_grid[y - 1][x + 1] == 0) {
                        grid[y - 1][x]->selected_tileset = 0;
                        grid[y - 1][x]->selected_frame = 2;
                    }

                    grid[y - 1][x]->collision_box_offset =
                        CHL::point(0, TILE_SIZE / 2);
                    grid[y - 1][x]->collision_box.y = TILE_SIZE / 2;
                }
                if (bottom &&
                    grid[y + 1][x]->selected_tileset == default_tileset &&
                    grid[y + 1][x]->selected_frame == default_frame) {
                    if (left_bonds && right_bonds &&
                        map_grid[y + 1][x - 1] == 0 &&
                        map_grid[y + 1][x + 1] == 0) {
                        grid[y + 1][x]->selected_tileset = 2;
                        grid[y + 1][x]->selected_frame = 5;
                    } else if (left_bonds && map_grid[y + 1][x - 1] == 0) {
                        grid[y + 1][x]->selected_tileset = 2;
                        grid[y + 1][x]->selected_frame = 0;
                    } else if (right_bonds && map_grid[y + 1][x + 1] == 0) {
                        grid[y + 1][x]->selected_tileset = 2;
                        grid[y + 1][x]->selected_frame = 2;
                    } else {
                        grid[y + 1][x]->selected_tileset = 2;
                        grid[y + 1][x]->selected_frame = 1;
                    }
                }
                if (left &&
                    grid[y][x - 1]->selected_tileset == default_tileset &&
                    grid[y][x - 1]->selected_frame == default_frame) {
                    grid[y][x - 1]->selected_tileset = 1;
                    grid[y][x - 1]->selected_frame = 2;
                }
                if (right &&
                    grid[y][x + 1]->selected_tileset == default_tileset &&
                    grid[y][x + 1]->selected_frame == default_frame) {
                    grid[y][x + 1]->selected_tileset = 1;
                    grid[y][x + 1]->selected_frame = 0;
                }
                if (bottom && right && map_grid[y + 1][x + 1] == 1) {
                    grid[y + 1][x + 1]->selected_tileset = 1;
                    grid[y + 1][x + 1]->selected_frame = 4;
                }
                if (bottom && left && map_grid[y + 1][x - 1] == 1) {
                    grid[y + 1][x - 1]->selected_tileset = 1;
                    grid[y + 1][x - 1]->selected_frame = 3;
                }
                if (top && right && map_grid[y - 1][x + 1] == 1) {
                    grid[y - 1][x + 1]->selected_tileset = 2;
                    grid[y - 1][x + 1]->selected_frame = 4;
                }
                if (top && left && map_grid[y - 1][x - 1] == 1) {
                    grid[y - 1][x - 1]->selected_tileset = 2;
                    grid[y - 1][x - 1]->selected_frame = 3;
                }
            }
        }
    }

    for (int y = 0; y < y_size; y++) {
        for (int x = 0; x < x_size; x++) {
            if (map_grid[y][x] == 1) {
                bool left_bonds = x - 1 >= 0;
                bool right_bonds = x + 1 < x_size;
                bool top_bonds = y - 1 >= 0;
                bool bot_bonds = y + 1 < y_size;

                bool horisontal_bonds = left_bonds && right_bonds;
                bool vertical_bonds = top_bonds && bot_bonds;

                bool bonds = vertical_bonds && horisontal_bonds;

                bool vertical = horisontal_bonds && map_grid[y][x - 1] == 0 &&
                                map_grid[y][x + 1] == 0;
                bool horisontal =
                    bonds && map_grid[y - 1][x] == 0 && map_grid[y + 1][x] == 0;

                if (vertical) {
                    if (top_bonds && map_grid[y - 1][x] == 0) {
                        grid[y][x]->selected_tileset = 2;
                        grid[y][x]->selected_frame = 5;
                    } else if (bot_bonds && map_grid[y + 1][x] == 0) {
                        grid[y][x]->selected_tileset = 0;
                        grid[y][x]->selected_frame = 5;
                    } else {
                        grid[y][x]->selected_tileset = 1;
                        grid[y][x]->selected_frame = 5;
                    }
                }

                if (horisontal) {
                    if (left_bonds && map_grid[y][x - 1] == 0) {
                        grid[y][x]->selected_tileset = 2;
                        grid[y][x]->selected_frame = 6;
                    } else if (right_bonds && map_grid[y][x + 1] == 0) {
                        grid[y][x]->selected_tileset = 2;
                        grid[y][x]->selected_frame = 8;
                    }
                }

                if (vertical && horisontal) {
                    grid[y][x]->selected_tileset = 2;
                    grid[y][x]->selected_frame = 7;
                }
            }
        }
    }

    for (int y = 0; y < y_size; y++) {
        for (int x = 0; x < x_size; x++) {
            if (map_grid[y][x] == 1) {
                bool left_bonds = x - 1 >= 0;
                bool right_bonds = x + 1 < x_size;
                bool top_bonds = y - 1 >= 0;
                bool bot_bonds = y + 1 < y_size;

                bool horisontal_bonds = left_bonds && right_bonds;
                bool vertical_bonds = top_bonds && bot_bonds;

                bool bonds = vertical_bonds && horisontal_bonds;

                bool vertical =
                    bonds && map_grid[y][x - 1] == 0 && map_grid[y][x + 1] == 0;
                bool horisontal =
                    bonds && map_grid[y - 1][x] == 0 && map_grid[y + 1][x] == 0;

                if (vertical) {
                    if (map_grid[y + 1][x - 1] == 0 &&
                        map_grid[y + 1][x + 1] == 1 &&
                        map_grid[y + 1][x] == 1) {
                        grid[y + 1][x]->selected_tileset = 1;
                        grid[y + 1][x]->selected_frame = 6;
                    } else if (map_grid[y + 1][x - 1] == 1 &&
                               map_grid[y + 1][x + 1] == 0 &&
                               map_grid[y + 1][x] == 1) {
                        grid[y + 1][x]->selected_tileset = 0;
                        grid[y + 1][x]->selected_frame = 6;
                    } else if (map_grid[y + 1][x - 1] == 1 &&
                               map_grid[y + 1][x + 1] == 1 &&
                               map_grid[y + 1][x] == 1) {
                        grid[y + 1][x]->selected_tileset = 0;
                        grid[y + 1][x]->selected_frame = 8;
                    }

                    if (map_grid[y - 1][x - 1] == 1 &&
                        map_grid[y - 1][x + 1] == 0 &&
                        map_grid[y - 1][x] == 1) {
                        grid[y - 1][x]->selected_tileset = 0;
                        grid[y - 1][x]->selected_frame = 7;
                    } else if (map_grid[y - 1][x - 1] == 0 &&
                               map_grid[y - 1][x + 1] == 1 &&
                               map_grid[y - 1][x] == 1) {
                        grid[y - 1][x]->selected_tileset = 1;
                        grid[y - 1][x]->selected_frame = 7;
                    } else if (map_grid[y - 1][x - 1] == 1 &&
                               map_grid[y - 1][x + 1] == 1 &&
                               map_grid[y - 1][x] == 1) {
                        grid[y - 1][x]->selected_tileset = 1;
                        grid[y - 1][x]->selected_frame = 8;
                    }
                }
            }
        }
    }
    for (int y = 0; y < y_size; y++) {
        for (int x = 0; x < x_size; x++) {
            if (map_grid[y][x] == 1) {
                bool left_bonds = x - 1 >= 0;
                bool right_bonds = x + 1 < x_size;
                bool top_bonds = y - 1 >= 0;
                bool bot_bonds = y + 1 < y_size;

                bool horisontal_bonds = left_bonds && right_bonds;
                bool vertical_bonds = top_bonds && bot_bonds;

                bool bonds = vertical_bonds && horisontal_bonds;
                if (bonds) {
                    if (map_grid[y - 1][x] == 0 && map_grid[y + 1][x] == 1 &&
                        map_grid[y + 1][x + 1] == 1 &&
                        map_grid[y + 1][x - 1] == 0 &&
                        map_grid[y][x - 1] == 1 && map_grid[y][x + 1] == 1) {
                        grid[y][x]->selected_tileset = 0;
                        grid[y][x]->selected_frame = 10;
                    } else if (map_grid[y - 1][x] == 0 &&
                               map_grid[y + 1][x] == 1 &&
                               map_grid[y + 1][x + 1] == 0 &&
                               map_grid[y + 1][x - 1] == 1 &&
                               map_grid[y][x - 1] == 1 &&
                               map_grid[y][x + 1] == 1) {
                        grid[y][x]->selected_tileset = 0;
                        grid[y][x]->selected_frame = 9;
                    } else if (map_grid[y - 1][x] == 1 &&
                               map_grid[y][x + 1] == 1 &&
                               map_grid[y][x - 1] == 1 &&
                               map_grid[y + 1][x] == 0 &&
                               map_grid[y - 1][x + 1] == 1 &&
                               map_grid[y - 1][x - 1] == 0) {
                        grid[y][x]->selected_tileset = 1;
                        grid[y][x]->selected_frame = 12;
                    } else if (map_grid[y - 1][x] == 1 &&
                               map_grid[y][x + 1] == 1 &&
                               map_grid[y][x - 1] == 1 &&
                               map_grid[y + 1][x] == 0 &&
                               map_grid[y - 1][x + 1] == 0 &&
                               map_grid[y - 1][x - 1] == 1) {
                        grid[y][x]->selected_tileset = 1;
                        grid[y][x]->selected_frame = 11;
                    } else if (map_grid[y - 1][x] == 1 &&
                               map_grid[y][x + 1] == 1 &&
                               map_grid[y - 1][x + 1] == 0 &&
                               map_grid[y - 1][x - 1] == 0 &&
                               map_grid[y][x - 1] == 0 &&
                               map_grid[y + 1][x] == 0) {
                        grid[y][x]->selected_tileset = 2;
                        grid[y][x]->selected_frame = 10;
                    } else if (map_grid[y - 1][x] == 1 &&
                               map_grid[y][x - 1] == 1 &&
                               map_grid[y - 1][x - 1] == 0 &&
                               map_grid[y - 1][x + 1] == 0 &&
                               map_grid[y][x + 1] == 0 &&
                               map_grid[y + 1][x] == 0) {
                        grid[y][x]->selected_tileset = 2;
                        grid[y][x]->selected_frame = 9;
                    } else if (map_grid[y + 1][x] == 1 &&
                               map_grid[y][x + 1] == 1 &&
                               map_grid[y + 1][x + 1] == 0 &&
                               map_grid[y + 1][x - 1] == 0 &&
                               map_grid[y][x - 1] == 0 &&
                               map_grid[y - 1][x] == 0) {
                        grid[y][x]->selected_tileset = 1;
                        grid[y][x]->selected_frame = 10;
                    } else if (map_grid[y + 1][x] == 1 &&
                               map_grid[y][x - 1] == 1 &&
                               map_grid[y + 1][x - 1] == 0 &&
                               map_grid[y + 1][x + 1] == 0 &&
                               map_grid[y][x + 1] == 0 &&
                               map_grid[y - 1][x] == 0) {
                        grid[y][x]->selected_tileset = 1;
                        grid[y][x]->selected_frame = 9;
                    } else if (map_grid[y][x - 1] == 1 &&
                               map_grid[y][x + 1] == 1 &&
                               map_grid[y - 1][x - 1] == 0 &&
                               map_grid[y - 1][x] == 1 &&
                               map_grid[y + 1][x] == 1 &&
                               map_grid[y - 1][x + 1] == 1 &&
                               map_grid[y + 1][x + 1] == 0) {
                        grid[y][x]->selected_tileset = 2;
                        grid[y][x]->selected_frame = 11;
                    } else if (map_grid[y][x + 1] == 1 &&
                               map_grid[y][x - 1] == 1 &&
                               map_grid[y - 1][x + 1] == 0 &&
                               map_grid[y - 1][x] == 1 &&
                               map_grid[y + 1][x] == 1 &&
                               map_grid[y - 1][x - 1] == 1 &&
                               map_grid[y + 1][x - 1] == 0) {
                        grid[y][x]->selected_tileset = 2;
                        grid[y][x]->selected_frame = 12;
                    } else if (map_grid[y][x + 1] == 0 &&
                               map_grid[y][x - 1] == 1 &&
                               map_grid[y - 1][x] == 1 &&
                               map_grid[y + 1][x] == 1 &&
                               map_grid[y + 1][x + 1] == 1 &&
                               map_grid[y + 1][x - 1] == 0) {
                        grid[y][x]->selected_tileset = 0;
                        grid[y][x]->selected_frame = 7;
                    } else if (map_grid[y][x - 1] == 0 &&
                               map_grid[y][x + 1] == 1 &&
                               map_grid[y - 1][x] == 1 &&
                               map_grid[y + 1][x] == 1 &&
                               map_grid[y + 1][x - 1] == 1 &&
                               map_grid[y + 1][x + 1] == 0) {
                        grid[y][x]->selected_tileset = 1;
                        grid[y][x]->selected_frame = 7;
                    } else if (map_grid[y][x - 1] == 1 &&
                               map_grid[y][x + 1] == 1 &&
                               map_grid[y + 1][x] == 1 &&
                               map_grid[y + 1][x - 1] == 0 &&
                               map_grid[y + 1][x - 1] == 0 &&
                               map_grid[y - 1][x] == 0) {
                        grid[y][x]->selected_tileset = 0;
                        grid[y][x]->selected_frame = 3;
                    } else if (map_grid[y][x - 1] == 1 &&
                               map_grid[y][x + 1] == 1 &&
                               map_grid[y - 1][x] == 1 &&
                               map_grid[y - 1][x - 1] == 0 &&
                               map_grid[y - 1][x - 1] == 0 &&
                               map_grid[y + 1][x] == 0) {
                        grid[y][x]->selected_tileset = 0;
                        grid[y][x]->selected_frame = 4;
                    } else if (map_grid[y][x + 1] == 1 &&
                               map_grid[y][x - 1] == 0 &&
                               map_grid[y + 1][x] == 1 &&
                               map_grid[y + 1][x + 1] == 1 &&
                               map_grid[y - 1][x] == 1 &&
                               map_grid[y - 1][x + 1] == 0) {
                        grid[y][x]->selected_tileset = 1;
                        grid[y][x]->selected_frame = 6;
                    } else if (map_grid[y][x - 1] == 1 &&
                               map_grid[y][x + 1] == 0 &&
                               map_grid[y + 1][x] == 1 &&
                               map_grid[y + 1][x - 1] == 1 &&
                               map_grid[y - 1][x] == 1 &&
                               map_grid[y - 1][x - 1] == 0) {
                        grid[y][x]->selected_tileset = 0;
                        grid[y][x]->selected_frame = 6;
                    } else if (map_grid[y - 1][x + 1] == 0 &&
                               map_grid[y - 1][x] == 0 &&
                               map_grid[y][x - 1] == 0 &&
                               map_grid[y][x + 1] == 1 &&
                               map_grid[y + 1][x] == 1 &&
                               map_grid[y + 1][x + 1] == 0) {
                        grid[y][x]->selected_tileset = 1;
                        grid[y][x]->selected_frame = 10;
                    } else if (map_grid[y - 1][x - 1] == 0 &&
                               map_grid[y - 1][x] == 0 &&
                               map_grid[y][x + 1] == 0 &&
                               map_grid[y][x - 1] == 1 &&
                               map_grid[y + 1][x] == 1 &&
                               map_grid[y + 1][x - 1] == 0) {
                        grid[y][x]->selected_tileset = 1;
                        grid[y][x]->selected_frame = 9;
                    }
                } else {
                    if (vertical_bonds && right_bonds &&
                        map_grid[y + 1][x] == 0 && map_grid[y][x + 1] == 1 &&
                        map_grid[y - 1][x] == 1 &&
                        map_grid[y - 1][x + 1] == 0) {
                        grid[y][x]->selected_tileset = 1;
                        grid[y][x]->selected_frame = 11;
                    } else if (vertical_bonds && left_bonds &&
                               map_grid[y + 1][x] == 0 &&
                               map_grid[y][x - 1] == 1 &&
                               map_grid[y - 1][x] == 1 &&
                               map_grid[y - 1][x - 1] == 0) {
                        grid[y][x]->selected_tileset = 1;
                        grid[y][x]->selected_frame = 12;
                    } else if (vertical_bonds && right_bonds &&
                               map_grid[y - 1][x] == 0 &&
                               map_grid[y][x + 1] == 1 &&
                               map_grid[y + 1][x] == 1 &&
                               map_grid[y + 1][x + 1] == 0) {
                        grid[y][x]->selected_tileset = 0;
                        grid[y][x]->selected_frame = 9;
                    } else if (vertical_bonds && left_bonds &&
                               map_grid[y - 1][x] == 0 &&
                               map_grid[y][x - 1] == 1 &&
                               map_grid[y + 1][x] == 1 &&
                               map_grid[y + 1][x - 1] == 0) {
                        grid[y][x]->selected_tileset = 0;
                        grid[y][x]->selected_frame = 10;
                    }
                }
            }
        }
    }
    for (int y = 0; y < y_size; y++) {
        for (int x = 0; x < x_size; x++) {
            if (grid[y][x] != nullptr)
                /*update the texture coordinates*/
                grid[y][x]->update_points();
        }
    }
}
