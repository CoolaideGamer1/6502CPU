{ pkgs }: {
	deps = [
   pkgs.python38
		pkgs.clang_12
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
	];
}