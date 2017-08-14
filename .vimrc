"split navigations
nnoremap <C-J> <C-W><C-J>
nnoremap <C-K> <C-W><C-K>
nnoremap <C-L> <C-W><C-L>
nnoremap <C-H> <C-W><C-H>

syntax on
set number	
set relativenumber
set linebreak	
set showbreak=-- 	
set showmatch	
set visualbell	
set hlsearch	
set smartcase	
set ignorecase	
set incsearch	
set ruler
set autoindent	
set shiftwidth=4	
set smartindent	
set smarttab	
set softtabstop=4	
set ruler	
set undolevels=1000	
set backspace=indent,eol,start	
set cursorline

if filereadable(expand("~/.vimrc_background"))
   let base16colorspace=256
   source ~/.vimrc_background
endif
