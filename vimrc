"隐藏菜单
set go=

if &t_Co > 2 || has("gui_running")
    syntax on
    set hlsearch
endif
colorscheme desert    "使用沙漠配色方案
syntax enable

" 下面5行用来解决gVim菜单栏和右键菜单乱码问题
set encoding=utf8
set fenc=utf-8
set fencs=utf-8,ucs-bom,gb18030,gbk,gb2312,cp936
set langmenu=zh_CN.UTF-8
set imcmdline
source $VIMRUNTIME/delmenu.vim
source $VIMRUNTIME/menu.vim

set nobackup
set autochdir

" 解决gVim中提示框乱码
language message zh_CN.UTF-8

set fileencodings=utf-8,chinese,latin-1,gb18030   
if has("win32")  
      set fileencoding=chinese   
  else    
        set fileencoding=utf-8
    endif   

    "设置是否要备份    0110717添加   
    "if has("vms")
	"set nobackup
    "else
	"set backup
    "endif
    
    autocmd FileType text setlocal textwidth=100 "在一行长于78个字符时自动换行 220110717添

    "读入任何文件后自动换行 20110717添加
    autocmd BufReadPost *
    	\if line("'\"") >0 && line("'\"") <= line("$") |
    	\	exe "normal g`\"" |
    	\endif

    source $VIMRUNTIME/delmenu.vim   
    source $VIMRUNTIME/menu.vim  
    language messages zh_CN.utf-8

"自动识别文件类型，用文件类型plugin脚本，使用缩进定义文件
"filetype plugin indent on

"开启文件类型检测
filetype on
"检测到不同的类型加载相应的插件
filetype plugin on
"根据检测到的不同的类型采取不同的缩进方式
filetype indent on
"取消补全内容以分割子窗口形式出现，只显示补全列表
set completeopt=longest,menu
" add by liyun 2012-08-30
set smartindent "一个tab是4个字符
set tabstop=4  "按一次tab前进4个字符
set softtabstop=4 "用空格代替tab
set expandtab
set shiftwidth=4


" add by liyun 2012-08-30
set incsearch        "输入搜索内容的同时开始搜索
set number        "设置左边框行标
set cindent shiftwidth=4 "自动缩进4个字符
set autoindent
set history=1000    "保存1000条历史记录
set ruler        "在右下端显示光标所处的位置
set showcmd        "显示输入的命令
map Q gq        "将Q映射为gq模式
"在可视模式下拷贝已选择的文件，并在C/C++文件中查找。
vnoremap _g y:exe "grep /" .escape(@", '\\/') . "/ *.c *.cpp *.h"<CR>
"set backspace=indent,eol,start        "在Insert模式下退格键可以删除的内容    
"set autochdir /


"taglist 的设置
let Tlist_Ctags_Cmd='/usr/bin/ctags'
let Tlist_Show_One_File=1
let Tlist_OnlyWindow=1
let Tlist_Use_Right_Window=0
let Tlist_Sort_Type='name'
let Tlist_Exit_OnlyWindow=1
let Tlist_Show_Menu=1
let Tlist_Max_Submenu_Items=10
let Tlist_Max_Tag_lenth=20
let Tlist_Auto_Open=0
let Tlist_Close_On_Select=0
let Tlist_File_Fold_Auto_Close=1
let Tlist_GainFocus_On_ToggleOpen=0
let Tlist_Process_File_Always=1
let Tlist_WinHeight=10
let Tlist_WinWidth=20
let Tlist_Use_Horiz_Window=0
let Tlist_Inc_Winwidth=0

"定义快捷键的前缀，即<Leader>
let mapleader=";"
"设置显示标签列表子窗口快捷键
map<silent> <leader>tl :TlistToggle<CR>

"omnicppcomplete setting 
autocmd CursorMovedI * if pumvisible() == 0|pclose|endif
autocmd InsertLeave * if pumvisible() == 0|pclose|endif
set completeopt=menu,menuone
let OmniCpp_MayCompleteDot = 1 " autocomplete with .
let OmniCpp_MayCompleteArrow = 1 " autocomplete with ->
let OmniCpp_MayCompleteScope = 1 " autocomplete with ::
let OmniCpp_SelectFirstItem = 2 " select first item (but don't insert)
let OmniCpp_NamespaceSearch = 2 " search namespaces in this and included files
let OmniCpp_ShowPrototypeInAbbr = 1 " show function prototype  in popup window
let OmniCpp_GlobalScopeSearch=1
let OmniCpp_DisplayMode=1
let OmniCpp_DefaultNamespaces=["std"]

set tags=tags
"set tags=~/tool/include/tags



"omicppcomplete 的ctags的快捷键
set nocp
"au BufWritePost *.c,*.cpp,*.cc,*.h !ctags -R --c++-kinds=+p --fields=+iaS --extra=+q .
"map <F12> :!ctags -R --c++-kinds=+p --fields=+iaS --extra=+q .<CR>
map <F12> :!ctags -R .<CR>


"代码折叠
set fdm=marker
" for python
"autocmd FileType python set omnifunc=pythoncomplete#Complete
":map <F7> zf% 		"代码折叠在括号处
":map <F8> zd            "取消代码折

" for cscope add by liyun 2012-09-23
" cscope -Rbkq

nmap <C-\>s :cs find s <C-R>=expand("<cword>")<CR><CR>
nmap <C-\>g :cs find g <C-R>=expand("<cword>")<CR><CR>
nmap <C-\>c :cs find c <C-R>=expand("<cword>")<CR><CR>
nmap <C-\>t :cs find t <C-R>=expand("<cword>")<CR><CR>
nmap <C-\>e :cs find e <C-R>=expand("<cword>")<CR><CR>
nmap <C-\>f :cs find f <C-R>=expand("<cfile>")<CR><CR>
nmap <C-\>i :cs find i ^<C-R>=expand("<cfile>")<CR>$<CR>
nmap <C-\>d :cs find d <C-R>=expand("<cword>")<CR><CR>
:map <F6> :cs add /home/szqh97/Projects/VDNALive_3.5/cscope.out /home/szqh97/example/VDNALive_3.5
":map <F5> :cs add /home/szqh97/Projects/zeromq-3.2.4/cscope.out /home/szqh97/Projects/zeromq-3.2.4/
:map <F5> :cs add /home/szqh97/tool/ffmpeg-2.1.1/cscope.out /home/szqh97/tool/ffmpeg-2.1.1/
:map <F7> :cs add /usr/src/linux-3.5/cscope.out /usr/src/linux-3.5/                                                                                                                          

" for add date in vim 
 imap <F3> add by szqh97 <C-R>=strftime("%Y-%m-%d %H:%M:%S")<CR>
"set vim font 
"set guifont=Courier\ New\ 12
set guifont=Ubuntu\ Mono\ 16

autocmd! BufRead,BufNewFile,BufEnter *.{c,cpp,h,javascript} call CSyntaxAfter()

"add by szqh97 2013-05-05 19:36:52 for python
au BufNewFile,BufRead *.py,*.pyw setf python

"add by szqh97 2013-06-30 11:03:10I
set tags=tags
"set tags+=/usr/lib/python2.7/tags
"set tags+=/usr/local/lib/python2.7/tags
"set tags+=/home/szqh97/example/livebox/src/processor/tags
"set tags+=/home/szqh97/Projects/VDNALive_3.5/tags
"set tags+=/usr/include/tags
"set tags+=/usr/lib/tags
"set tags+=/usr/src/linux-3.5/tags
"set tags+=/home/szqh97/example/unp/unpv13e/tags
"set tags+=/home/szqh97/example/projects/flac-1.2.1/tags
"set tags+=/home/szqh97/Projects/VDNALive_3.5/tags
set tags+=/home/szqh97/.vim/ctags/cpp_src/tags   "cpp_src 经典tags
set tags+=/usr/local/include/opencv2/tags
"set tags+=/home/szqh97/tool/ffmpeg-2.1.1/tags


" for pydiction
filetype off
filetype plugin indent off
let g:pydiction_location = '/home/szqh97/tool/pydiction/complete-dict'
let g:pydiction_menu_height = 20 
filetype plugin indent on
" for SuperTab
au Filetype python call AddPythonFunclist()
function AddPythonFunclist()
    set dictionary+=/home/szqh97/tool/pydiction/complete-dict
    set complete+=k
endfunction

filetype off
filetype plugin indent off
set runtimepath+=/home/szqh97/tools/go-c51e9abbb4fd/misc/vim

filetype plugin indent on
syntax on
"let g:SuperTabRetainCompletionType=2
"let g:SuperTabDefaultCompletionType="<C-x><C-n>"
let g:SuperTabRetainCompletionType=0
let g:SuperTabDefaultCompletionType="<C-P>"
imap <C-\> <C-x><C-o>
