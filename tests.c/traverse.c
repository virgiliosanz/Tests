#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <sys/stat.h>
#include <fts.h>
#include <string.h>

int main(int argc, char **argv)
{
	char *dot[] = {".", 0};
	char **paths = argc > 1 ? argv + 1 : dot;

	FTS *tree = fts_open(paths, FTS_NOCHDIR, 0);
	if (!tree) {
		perror("fts_open");
		return 1;
	}

	FTSENT *node;
	while ((node = fts_read(tree))) {
		if (node->fts_level > 0 && node->fts_name[0] == '.')
			fts_set(tree, node, FTS_SKIP);
		else if (node->fts_info & FTS_F) {
			printf("%s (f) times a: %s, c: %s, m: %s\n",
				node->fts_accpath,
				ctime(&node->fts_statp->st_atime),
				ctime(&node->fts_statp->st_ctime),
				ctime(&node->fts_statp->st_mtime));

			/* if fts_open is not given FTS_NOCHDIR,
			 * fts may change the program's current working directory */
		} else if (node->fts_info & FTS_D) {
			printf("%s (D) times - a: %s, c: %s, m: %s\n",
				node->fts_accpath,
				ctime(&node->fts_statp->st_atime),
				ctime(&node->fts_statp->st_ctime),
				ctime(&node->fts_statp->st_mtime));
		}
	}
	if (errno) {
		perror("fts_read");
		return 1;
	}

	if (fts_close(tree)) {
		perror("fts_close");
		return 1;
	}

	return 0;
}
