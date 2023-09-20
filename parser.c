#include "shell.h"

/**
 * is_exec - Determines if a file is an executable command.
 * @inf: The info struct.
 * @fpath: The path to the file.
 *
 * Return: 1 if true, 0 otherwise.
 */
int is_exec(info_t *inf, char *fpath)
{
    struct stat st;

    (void)inf;
    if (!fpath || stat(fpath, &st))
        return (0);

    if (st.st_mode & S_IFREG)
    {
        return (1);
    }
    return (0);
}

/**
 * dupli_chars - Duplicates characters from a string within a specified range.
 * @pathstr: The PATH string.
 * @st_idx: The starting index.
 * @sp_idx: The stopping index.
 *
 * Return: Pointer to a new buffer.
 */
char *dupli_chars(char *pathstr, int st_idx, int sp_idx)
{
    static char buff[1024];
    int a = 0, b = 0;

    for (b = 0, a = st_idx; a < sp_idx; a++)
    {
        if (pathstr[a] != ':')
        {
            buff[b++] = pathstr[a];
        }
    }
    buff[b] = 0;
    return (buff);
}

/**
 * find_comm_path - Finds the full path of a command in the PATH string.
 * @inf: The info struct.
 * @pathstr: The PATH string.
 * @comm: The command to find.
 *
 * Return: Full path of the command if found, or NULL.
 */
char *find_comm_path(info_t *inf, char *pathstr, char *comm)
{
    int n = 0, cur_pos = 0;
    char *path;

    if (!pathstr)
        return (NULL);

    if ((_strlen(comm) > 2) && starts(comm, "./"))
    {
        if (is_exec(inf, comm))
            return (comm);
    }

    while (1)
    {
        if (!pathstr[n] || pathstr[n] == ':')
        {
            path = dupli_chars(pathstr, cur_pos, n);
            if (!*path)
                _strcat(path, comm);
            else
            {
                _strcat(path, "/");
                _strcat(path, comm);
            }
            if (is_exec(inf, path))
                return (path);

            if (!pathstr[n])
                break;
            cur_pos = n;
        }
        n++;
    }
    return (NULL);
}

