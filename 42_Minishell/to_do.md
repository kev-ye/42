- [x] echo options multi -n
- [x] seg with exit cmd and no args - (returns code 139 - it may help...)
- [x] export env name with spaces (ex: export "ksjfhg  fglkj")
- [x] change PWD and OLDPWD in `cd' cmd
- [x] unset PATH, env must not be found (ex: unset PATH; env)
- [x] .. : command not found
- [x] . -> is short for "source cmd", and source is a builtin cmd, we don't need do this
- [x] cat << f1 (then type anything, enter, and CTRL-D - bash displays the last line entered)
- [x] mix case: ls | wc > f1 | wc
- [x] mix case: ls | wc << f1
- [x] mix case: ls | wc > f1 | echo test | wc > f2
- [x] mix case: ls ; ls | wc ; echo test ; ls | wc << 1 ; cat << 1 << 2 ; ls (doube input first)
- [x] ls > f1 | echo test < f2 | echo test > f3 | echo test > f4 ; echo test > f5
- [x] ls ; wc < f1 ; ls > f1 ; echo test
- [x] wc < f1 : seg
- [x] ls | ./minishill : command not found, idk why
- [x] cat << f$?
- [x] export lol ; export "lol = fuck" tt ---> result : ttl ???
- [x] check env, maybe is not complet
- [x] some change with exec -> need to check (unset PATH get some new case)
- [x] add signal for CTRL-\
- [x] cd : no more 2 args
- [x] builtin can launch with redir but no with pipe
- [x] leak with fd : check \[first/inter/last\]_cmd.c
- [x] unset with multi args no fonction + msg error like export