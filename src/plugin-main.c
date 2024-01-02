/*
Plugin Name
Copyright (C) <Year> <Developer> <Email Address>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program. If not, see <https://www.gnu.org/licenses/>
*/

#include <obs-module.h>
#include <obs-frontend-api.h>
#include <obs-hotkeys.h>

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("myplugin", "en-US")

static int team1_score = 0;
static int team2_score = 0;
static char* team1_name = "Team 1";
static char* team2_name = "Team 2";
static char* team1_logo_path = NULL;
static char* team2_logo_path = NULL;

static obs_hotkey_id increase_team1_hotkey;
static obs_hotkey_id decrease_team1_hotkey;
static obs_hotkey_id increase_team2_hotkey;
static obs_hotkey_id decrease_team2_hotkey;
static obs_hotkey_id reset_scores_hotkey;

void load_team_settings()
{
    team1_name = obs_data_get_string(obs_data_get_root(), "team1_name");
    team2_name = obs_data_get_string(obs_data_get_root(), "team2_name");
    team1_logo_path = obs_data_get_string(obs_data_get_root(), "team1_logo_path");
    team2_logo_path = obs_data_get_string(obs_data_get_root(), "team2_logo_path");
}

void increase_team1_score(obs_hotkey_t* hotkey, obs_hotkey_id id, void* data)
{
    team1_score++;
    blog(LOG_INFO, "%s Score: %d", team1_name, team1_score);
}

void decrease_team1_score(obs_hotkey_t* hotkey, obs_hotkey_id id, void* data)
{
    team1_score--;
    blog(LOG_INFO, "%s Score: %d", team1_name, team1_score);
}

void increase_team2_score(obs_hotkey_t* hotkey, obs_hotkey_id id, void* data)
{
    team2_score++;
    blog(LOG_INFO, "%s Score: %d", team2_name, team2_score);
}

void decrease_team2_score(obs_hotkey_t* hotkey, obs_hotkey_id id, void* data)
{
    team2_score--;
    blog(LOG_INFO, "%s Score: %d", team2_name, team2_score);
}

void reset_scores(obs_hotkey_t* hotkey, obs_hotkey_id id, void* data)
{
    team1_score = 0;
    team2_score = 0;
    blog(LOG_INFO, "Scores reset to 0");
}

bool obs_module_load(void)
{
    blog(LOG_INFO, "Scoreboard Plugin loaded.");

    load_team_settings();

    increase_team1_hotkey = obs_hotkey_register_frontend("IncreaseTeam1", "Increase Team 1 Score",
                                                        increase_team1_score, NULL);
    obs_hotkey_load(increase_team1_hotkey);

    decrease_team1_hotkey = obs_hotkey_register_frontend("DecreaseTeam1", "Decrease Team 1 Score",
                                                        decrease_team1_score, NULL);
    obs_hotkey_load(decrease_team1_hotkey);

    increase_team2_hotkey = obs_hotkey_register_frontend("IncreaseTeam2", "Increase Team 2 Score",
                                                        increase_team2_score, NULL);
    obs_hotkey_load(increase_team2_hotkey);

    decrease_team2_hotkey = obs_hotkey_register_frontend("DecreaseTeam2", "Decrease Team 2 Score",
                                                        decrease_team2_score, NULL);
    obs_hotkey_load(decrease_team2_hotkey);

    reset_scores_hotkey = obs_hotkey_register_frontend("ResetScores", "Reset Scores",
                                                      reset_scores, NULL);
    obs_hotkey_load(reset_scores_hotkey);

    return true;
}

void obs_module_unload(void)
{
    blog(LOG_INFO, "Scoreboard Plugin unloaded.");

    obs_hotkey_unregister(increase_team1_hotkey);
    obs_hotkey_unregister(decrease_team1_hotkey);
    obs_hotkey_unregister(increase_team2_hotkey);
    obs_hotkey_unregister(decrease_team2_hotkey);
    obs_hotkey_unregister(reset_scores_hotkey);

    bfree(team1_name);
    bfree(team2_name);
    bfree(team1_logo_path);
    bfree(team2_logo_path);
}
