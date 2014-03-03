/*
 * Copyright © 2014 Canonical Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors:
 *      Ted Gould <ted@canonical.com>
 */

#include <gtest/gtest.h>
#include <gio/gio.h>

extern "C" {
#include "indicator-sound-service.h"
#include "vala-mocks.h"
}

class SoundMenuTest : public ::testing::Test
{
	protected:
		GTestDBus * bus = nullptr;

		virtual void SetUp() {
			bus = g_test_dbus_new(G_TEST_DBUS_NONE);
			g_test_dbus_up(bus);
		}

		virtual void TearDown() {
			g_test_dbus_down(bus);
			g_clear_object(&bus);
		}
};

TEST_F(SoundMenuTest, BasicObject) {
	SoundMenu * menu = sound_menu_new (nullptr, SOUND_MENU_DISPLAY_FLAGS_NONE);

	g_clear_object(&menu);
	return;
}
