<?php

return function() {
	if (strlen(getenv("DDNS_GIT_BRANCH"))) {
		$git_branch = getenv("DDNS_GIT_BRANCH");
	} else {
		$git_branch = XPHPUtils::shell_exec("git rev-parse --abbrev-ref HEAD");
	}

	return trim($git_branch);
};
