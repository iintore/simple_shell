#include "shell.h"

/**
 * cd_and_dot - changes to previous parent directory
 *
 * @data: relevant data
 *
 * Return: nothing
 */
void cd_and_dot(data_shell *data)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, data);
	dir = datash->args[1];
	if (_strcmp(".", dir) == 0)
	
		set_env("PWD", cp_pwd, data);
		free(cp_pwd);
		return;
	}
	if (_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	rev_string(cp_strtok_pwd);
	cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			rev_string(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		set_env("PWD", cp_strtok_pwd, data);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", data);
	}
	data->status = 0;
	free(cp_pwd);
}

/**
 * change_to - changes to next directory of choice
 * @data:relevant data
 * Return: no return
 */
void change_to(data_shell *data)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = data->args[1];
	if (chdir(dir) == -1)
	{
		get_error(data, 2);
		return;
	}

	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, data);

	cp_dir = _strdup(dir);
	set_env("PWD", cp_dir, data);

	free(cp_pwd);
	free(cp_dir);

	data->status = 0;

	chdir(dir);
}

/**
 * change_to_prev - changes to the previous directory
 *
 * @data: data relevant
 * Return: northing
 */
void change_to_prev(data_shell *data)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	p_oldpwd = _getenv("OLDPWD", data->_environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdup(p_oldpwd);

	set_env("OLDPWD", cp_pwd, data);

	if (chdir(cp_oldpwd) == -1)
		set_env("PWD", cp_pwd, data);
	else
		set_env("PWD", cp_oldpwd, data);

	p_pwd = _getenv("PWD", data->_environ);

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	data->status = 0;

	chdir(p_pwd);
}

/**
 * change_to_home - changes to home directory
 *
 * @data: data relevant (environ)
 * Return: no return
 */
void change_to_home(data_shell *data)
{
	char *p, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p = _strdup(pwd);

	home = _getenv("HOME", data->_environ);

	if (home == NULL)
	{
		set_env("OLDPWD", p, data);
		free(p);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error(data, 2);
		free(p);
		return;
	}

	set_env("OLDPWD", p, data);
	set_env("PWD", home, data);
	free(p);
	data->status = 0;
}
