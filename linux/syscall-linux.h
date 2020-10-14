#ifndef _SYSCALL_LINUX_H
#define _SYSCALL_LINUX_H
#define LIA64_ni_syscall		1024
#define LIA64_exit			1025
#define LIA64_read			1026
#define LIA64_write			1027
#define LIA64_open			1028
#define LIA64_close			1029
#define LIA64_creat			1030
#define LIA64_link			1031
#define LIA64_unlink			1032
#define LIA64_execve			1033
#define LIA64_chdir			1034
#define LIA64_fchdir			1035
#define LIA64_utimes			1036
#define LIA64_mknod			1037
#define LIA64_chmod			1038
#define LIA64_chown			1039
#define LIA64_lseek			1040
#define LIA64_getpid			1041
#define LIA64_getppid			1042
#define LIA64_mount			1043
#define LIA64_umount			1044
#define LIA64_setuid			1045
#define LIA64_getuid			1046
#define LIA64_geteuid			1047
#define LIA64_ptrace			1048
#define LIA64_access			1049
#define LIA64_sync			1050
#define LIA64_fsync			1051
#define LIA64_fdatasync			1052
#define LIA64_kill			1053
#define LIA64_rename			1054
#define LIA64_mkdir			1055
#define LIA64_rmdir			1056
#define LIA64_dup			1057
#define LIA64_pipe			1058
#define LIA64_times			1059
#define LIA64_brk			1060
#define LIA64_setgid			1061
#define LIA64_getgid			1062
#define LIA64_getegid			1063
#define LIA64_acct			1064
#define LIA64_ioctl			1065
#define LIA64_fcntl			1066
#define LIA64_umask			1067
#define LIA64_chroot			1068
#define LIA64_ustat			1069
#define LIA64_dup2			1070
#define LIA64_setreuid			1071
#define LIA64_setregid			1072
#define LIA64_getresuid			1073
#define LIA64_setresuid			1074
#define LIA64_getresgid			1075
#define LIA64_setresgid			1076
#define LIA64_getgroups			1077
#define LIA64_setgroups			1078
#define LIA64_getpgid			1079
#define LIA64_setpgid			1080
#define LIA64_setsid			1081
#define LIA64_getsid			1082
#define LIA64_sethostname		1083
#define LIA64_setrlimit			1084
#define LIA64_getrlimit			1085
#define LIA64_getrusage			1086
#define LIA64_gettimeofday		1087
#define LIA64_settimeofday		1088
#define LIA64_select			1089
#define LIA64_poll			1090
#define LIA64_symlink			1091
#define LIA64_readlink			1092
#define LIA64_uselib			1093
#define LIA64_swapon			1094
#define LIA64_swapoff			1095
#define LIA64_reboot			1096
#define LIA64_truncate			1097
#define LIA64_ftruncate			1098
#define LIA64_fchmod			1099
#define LIA64_fchown			1100
#define LIA64_getpriority		1101
#define LIA64_setpriority		1102
#define LIA64_statfs			1103
#define LIA64_fstatfs			1104
/* unused; used to be LIA64_ioperm */
#define LIA64_semget			1106
#define LIA64_semop			1107
#define LIA64_semctl			1108
#define LIA64_msgget			1109
#define LIA64_msgsnd			1110
#define LIA64_msgrcv			1111
#define LIA64_msgctl			1112
#define LIA64_shmget			1113
#define LIA64_shmat			1114
#define LIA64_shmdt			1115
#define LIA64_shmctl			1116
/* also known as klogctl() in GNU libc: */
#define LIA64_syslog			1117
#define LIA64_setitimer			1118
#define LIA64_getitimer			1119
#define LIA64_old_stat			1120
#define LIA64_old_lstat			1121
#define LIA64_old_fstat			1122
#define LIA64_vhangup			1123
#define LIA64_lchown			1124
#define LIA64_vm86			1125
#define LIA64_wait4			1126
#define LIA64_sysinfo			1127
#define LIA64_clone			1128
#define LIA64_setdomainname		1129
#define LIA64_uname			1130
#define LIA64_adjtimex			1131
#define LIA64_create_module		1132
#define LIA64_init_module		1133
#define LIA64_delete_module		1134
#define LIA64_get_kernel_syms		1135
#define LIA64_query_module		1136
#define LIA64_quotactl			1137
#define LIA64_bdflush			1138
#define LIA64_sysfs			1139
#define LIA64_personality		1140
#define LIA64_afs_syscall		1141
#define LIA64_setfsuid			1142
#define LIA64_setfsgid			1143
#define LIA64_getdents			1144
#define LIA64_flock			1145
#define LIA64_readv			1146
#define LIA64_writev			1147
#define LIA64_pread			1148
#define LIA64_pwrite			1149
#define LIA64__sysctl			1150
#define LIA64_mmap			1151
#define LIA64_munmap			1152
#define LIA64_mlock			1153
#define LIA64_mlockall			1154
#define LIA64_mprotect			1155
#define LIA64_mremap			1156
#define LIA64_msync			1157
#define LIA64_munlock			1158
#define LIA64_munlockall		1159
#define LIA64_sched_getparam		1160
#define LIA64_sched_setparam		1161
#define LIA64_sched_getscheduler	1162
#define LIA64_sched_setscheduler	1163
#define LIA64_sched_yield		1164
#define LIA64_sched_get_priority_max	1165
#define LIA64_sched_get_priority_min	1166
#define LIA64_sched_rr_get_interval	1167
#define LIA64_nanosleep			1168
#define LIA64_nfsservctl		1169
#define LIA64_prctl			1170
#define LIA64_mmap2			1172
#define LIA64_pciconfig_read		1173
#define LIA64_pciconfig_write		1174
#define LIA64_perfmonctl		1175
#define LIA64_sigaltstack		1176
#define LIA64_rt_sigaction		1177
#define LIA64_rt_sigpending		1178
#define LIA64_rt_sigprocmask		1179
#define LIA64_rt_sigqueueinfo		1180
#define LIA64_rt_sigreturn		1181
#define LIA64_rt_sigsuspend		1182
#define LIA64_rt_sigtimedwait		1183
#define LIA64_getcwd			1184
#define LIA64_capget			1185
#define LIA64_capset			1186
#define LIA64_sendfile			1187
#define LIA64_getpmsg			1188
#define LIA64_putpmsg			1189
#define LIA64_socket			1190
#define LIA64_bind			1191
#define LIA64_connect			1192
#define LIA64_listen			1193
#define LIA64_accept			1194
#define LIA64_getsockname		1195
#define LIA64_getpeername		1196
#define LIA64_socketpair		1197
#define LIA64_send			1198
#define LIA64_sendto			1199
#define LIA64_recv			1200
#define LIA64_recvfrom			1201
#define LIA64_shutdown			1202
#define LIA64_setsockopt		1203
#define LIA64_getsockopt		1204
#define LIA64_sendmsg			1205
#define LIA64_recvmsg			1206
#define LIA64_pivot_root		1207
#define LIA64_mincore			1208
#define LIA64_madvise			1209
#define LIA64_stat			1210
#define LIA64_lstat			1211
#define LIA64_fstat			1212
#define LIA64_clone2			1213
#define LIA64_getdents64		1214
#define LIA64_getunwind			1215
#define LIA64_readahead			1216
#define LIA64_setxattr			1217
#define LIA64_lsetxattr			1218
#define LIA64_fsetxattr			1219
#define LIA64_getxattr			1220
#define LIA64_lgetxattr			1221
#define LIA64_fgetxattr			1222
#define LIA64_listxattr			1223
#define LIA64_llistxattr		1224
#define LIA64_flistxattr		1225
#define LIA64_removexattr		1226
#define LIA64_lremovexattr		1227
#define LIA64_fremovexattr		1228
#define LIA64_tkill			1229
#define LIA64_futex			1230
#define LIA64_sched_setaffinity		1231
#define LIA64_sched_getaffinity		1232
#define LIA64_set_tid_address		1233
#define LIA64_fadvise64			1234
#define LIA64_tgkill			1235
#define LIA64_exit_group		1236
#define LIA64_lookup_dcookie		1237
#define LIA64_io_setup			1238
#define LIA64_io_destroy		1239
#define LIA64_io_getevents		1240
#define LIA64_io_submit			1241
#define LIA64_io_cancel			1242
#define LIA64_epoll_create		1243
#define LIA64_epoll_ctl			1244
#define LIA64_epoll_wait		1245
#define LIA64_restart_syscall		1246
#define LIA64_semtimedop		1247
#define LIA64_timer_create		1248
#define LIA64_timer_settime		1249
#define LIA64_timer_gettime		1250
#define LIA64_timer_getoverrun		1251
#define LIA64_timer_delete		1252
#define LIA64_clock_settime		1253
#define LIA64_clock_gettime		1254
#define LIA64_clock_getres		1255
#define LIA64_clock_nanosleep		1256
#define LIA64_fstatfs64			1257
#define LIA64_statfs64			1258
#define LIA64_mbind			1259
#define LIA64_get_mempolicy		1260
#define LIA64_set_mempolicy		1261
#define LIA64_mq_open			1262
#define LIA64_mq_unlink			1263
#define LIA64_mq_timedsend		1264
#define LIA64_mq_timedreceive		1265
#define LIA64_mq_notify			1266
#define LIA64_mq_getsetattr		1267
#define LIA64_kexec_load		1268
#define LIA64_vserver			1269
#define LIA64_waitid			1270
#define LIA64_add_key			1271
#define LIA64_request_key		1272
#define LIA64_keyctl			1273
#define LIA64_ioprio_set		1274
#define LIA64_ioprio_get		1275
#define LIA64_move_pages		1276
#define LIA64_inotify_init		1277
#define LIA64_inotify_add_watch		1278
#define LIA64_inotify_rm_watch		1279
#define LIA64_migrate_pages		1280
#define LIA64_openat			1281
#define LIA64_mkdirat			1282
#define LIA64_mknodat			1283
#define LIA64_fchownat			1284
#define LIA64_futimesat			1285
#define LIA64_newfstatat		1286
#define LIA64_unlinkat			1287
#define LIA64_renameat			1288
#define LIA64_linkat			1289
#define LIA64_symlinkat			1290
#define LIA64_readlinkat		1291
#define LIA64_fchmodat			1292
#define LIA64_faccessat			1293
#define LIA64_pselect6			1294
#define LIA64_ppoll			1295
#define LIA64_unshare			1296
#define LIA64_splice			1297
#define LIA64_set_robust_list		1298
#define LIA64_get_robust_list		1299
#define LIA64_sync_file_range		1300
#define LIA64_tee			1301
#define LIA64_vmsplice			1302
#define LIA64_fallocate			1303
#define LIA64_getcpu			1304
#define LIA64_epoll_pwait		1305
#define LIA64_utimensat			1306
#define LIA64_signalfd			1307
#define LIA64_timerfd			1308
#define LIA64_eventfd			1309
#define LIA64_timerfd_create		1310
#define LIA64_timerfd_settime		1311
#define LIA64_timerfd_gettime		1312
#define LIA64_signalfd4			1313
#define LIA64_eventfd2			1314
#define LIA64_epoll_create1		1315
#define LIA64_dup3			1316
#define LIA64_pipe2			1317
#define LIA64_inotify_init1		1318
#define LIA64_preadv			1319
#define LIA64_pwritev			1320
#define LIA64_rt_tgsigqueueinfo		1321
#define LIA64_recvmmsg			1322
#define LIA64_fanotify_init		1323
#define LIA64_fanotify_mark		1324
#define LIA64_prlimit64			1325
#define LIA64_name_to_handle_at		1326
#define LIA64_open_by_handle_at  	1327
#define LIA64_clock_adjtime		1328
#define LIA64_syncfs			1329
#define LIA64_setns			1330
#define LIA64_sendmmsg			1331
#define LIA64_process_vm_readv		1332
#define LIA64_process_vm_writev		1333
#define LIA64_accept4			1334
#define LIA64_finit_module		1335
#define LIA64_sched_setattr		1336
#define LIA64_sched_getattr		1337
#define LIA64_renameat2			1338
#define LIA64_getrandom			1339
#define LIA64_memfd_create		1340
#define LIA64_bpf			1341
#define LIA64_execveat			1342
#define LIA64_userfaultfd		1343
#define LIA64_membarrier		1344
#define LIA64_kcmp			1345
#define LIA64_mlock2			1346
#define LIA64_copy_file_range		1347
#define LIA64_preadv2			1348
#define LIA64_pwritev2			1349

#endif /* _SKI_SYSCALL_LINUX_H */