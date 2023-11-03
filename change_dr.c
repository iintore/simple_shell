#include "custom_shell.h"

/**
 * move_up_directory - changes to the previous parent directory
 *
 * @data: relevant data
 *
 * Return: nothing
 */
void move_up_directory(data_shell *data)
{
    char current_dir[PATH_MAX];
    char *directory, *copied_current_dir, *copied_strtok_directory;

    getcwd(current_dir, sizeof(current_dir));
    copied_current_dir = _strdup(current_dir);
    set_custom_env("OLD_DIR", copied_current_dir, data);
    directory = data->args[1];

    if (_custom_strcmp(".", directory) == 0)
    {
        set_custom_env("CURRENT_DIR", copied_current_dir, data);
        free(copied_current_dir);
        return;
    }

    if (_custom_strcmp("/", copied_current_dir) == 0)
    {
        free(copied_current_dir);
        return;
    }

    copied_strtok_directory = copied_current_dir;
    reverse_string(copied_strtok_directory);
    copied_strtok_directory = _custom_strtok(copied_strtok_directory, "/");
    if (copied_strtok_directory != NULL)
    {
        copied_strtok_directory = _custom_strtok(NULL, "\0");

        if (copied_strtok_directory != NULL)
            reverse_string(copied_strtok_directory);
    }

    if (copied_strtok_directory != NULL)
    {
        chdir(copied_strtok_directory);
        set_custom_env("CURRENT_DIR", copied_strtok_directory, data);
    }
    else
    {
        chdir("/");
        set_custom_env("CURRENT_DIR", "/", data);
    }
    data->custom_status = 0;
    free(copied_current_dir);
}

/**
 * move_to_directory - changes to the next directory of choice
 * @data: relevant data
 * Return: no return
 */
void move_to_directory(data_shell *data)
{
    char current_dir[PATH_MAX];
    char *directory, *copied_current_dir, *copied_directory;

    getcwd(current_dir, sizeof(current_dir));
    directory = data->args[1];

    if (chdir(directory) == -1)
    {
        custom_get_error(data, 2);
        return;
    }

    copied_current_dir = _strdup(current_dir);
    set_custom_env("OLD_DIR", copied_current_dir, data);

    copied_directory = _strdup(directory);
    set_custom_env("CURRENT_DIR", copied_directory, data);

    free(copied_current_dir);
    free(copied_directory);

    data->custom_status = 0;

    chdir(directory);
}

/**
 * move_to_previous - changes to the previous directory
 *
 * @data: data relevant
 * Return: nothing
 */
void move_to_previous(data_shell *data)
{
    char current_dir[PATH_MAX];
    char *previous_dir, *previous_old_dir, *copied_current_dir, *copied_old_dir;

    getcwd(current_dir, sizeof(current_dir));
    copied_current_dir = _strdup(current_dir);

    previous_old_dir = _get_custom_env("OLD_DIR", data->_custom_env);

    if (previous_old_dir == NULL)
        copied_old_dir = copied_current_dir;
    else
        copied_old_dir = _strdup(previous_old_dir);

    set_custom_env("OLD_DIR", copied_current_dir, data);

    if (chdir(copied_old_dir) == -1)
        set_custom_env("CURRENT_DIR", copied_current_dir, data);
    else
        set_custom_env("CURRENT_DIR", copied_old_dir, data);

    previous_dir = _get_custom_env("CURRENT_DIR", data->_custom_env);

    write(STDOUT_FILENO, previous_dir, _custom_strlen(previous_dir));
    write(STDOUT_FILENO, "\n", 1);

    free(copied_current_dir);
    if (previous_old_dir)
        free(copied_old_dir);

    data->custom_status = 0;

    chdir(previous_dir);
}

/**
 * move_to_home - changes to the home directory
 *
 * @data: data relevant (custom environment)
 * Return: no return
 */
void move_to_home(data_shell *data)
{
    char *path, *home_dir;
    char current_dir[PATH_MAX];

    getcwd(current_dir, sizeof(current_dir));
    path = _strdup(current_dir);

    home_dir = _get_custom_env("HOME_DIR", data->_custom_env);

    if (home_dir == NULL)
    {
        set_custom_env("OLD_DIR", path, data);
        free(path);
        return;
    }

    if (chdir(home_dir) == -1)
    {
        custom_get_error(data, 2);
        free(path);
        return;
    }

    set_custom_env("OLD_DIR", path, data);
    set_custom_env("CURRENT_DIR", home_dir, data);
    free(path);
    data->custom_status = 0;
}
