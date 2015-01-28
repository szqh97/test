let SessionLoad = 1
if &cp | set nocp | endif
let s:cpo_save=&cpo
set cpo&vim
inoremap <C-/> 
inoremap <expr> <Up> pumvisible() ? "\" : "\<Up>"
inoremap <expr> <Down> pumvisible() ? "\" : "\<Down>"
inoremap <expr> <S-Tab> pumvisible() ? "\" : "\<S-Tab>"
inoremap <silent> <SNR>23_AutoPairsReturn =AutoPairsReturn()
imap <F3> =strftime("%Y-%m-%d %H:%M:%S")
nmap d :cs find d =expand("<cword>")
nmap i :cs find i =expand("<cfile>")$
nmap f :cs find f =expand("<cfile>")
nmap e :cs find e =expand("<cword>")
nmap t :cs find t =expand("<cword>")
nmap c :cs find c =expand("<cword>")
nmap g :cs find g =expand("<cword>")
nmap s :cs find s =expand("<cword>")
nnoremap ;d :YcmShowDetailedDiagnostic
nmap <silent> ;w;t <Plug>VimwikiTabMakeDiaryNote
nmap <silent> ;w;w <Plug>VimwikiMakeDiaryNote
nmap <silent> ;w;i <Plug>VimwikiDiaryGenerateLinks
nmap <silent> ;wi <Plug>VimwikiDiaryIndex
nmap <silent> ;ws <Plug>VimwikiUISelect
nmap <silent> ;wt <Plug>VimwikiTabIndex
nmap <silent> ;ww <Plug>VimwikiIndex
map ;t <Plug>TaskList
nmap <silent> ;n <Plug>MarkClear
vmap <silent> ;r <Plug>MarkRegex
nmap <silent> ;r <Plug>MarkRegex
vmap <silent> ;m <Plug>MarkSet
nmap <silent> ;m <Plug>MarkSet
nmap ;ihn :IHN
nmap ;is :IHS:A
nmap ;ih :IHS
map <silent> ;tl :TlistToggle
vnoremap _g y:exe "grep /" .escape(@", '\\/') . "/ *.c *.cpp *.h"
nmap gx <Plug>NetrwBrowseX
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#NetrwBrowseX(expand("<cWORD>"),0)
map <F7> :cs add /home/li_yun/Projects/VideoCapture/trunk/livebox/cscope.out /home/li_yun/Projects/VideoCapture/trunk/livebox/
map <F5> :cs add /home/li_yun/Dropbox/livebox/src/cscope.out /home/li_yun/Dropbox/livebox/src/
map <F12> :!ctags -R .
map <F8> zd            "取消代码折
inoremap <expr> 	 pumvisible() ? "\" : "\	"
imap  =CtrlXPP()
imap  
imap ;ihn :IHN
imap ;is :IHS:A
imap ;ih :IHS
let &cpo=s:cpo_save
unlet s:cpo_save
set autochdir
set autoindent
set autowriteall
set background=dark
set backspace=indent,eol,start
set balloonexpr=BalloonDeclaration()
set cindent
set completefunc=youcompleteme#Complete
set completeopt=menuone
set cpoptions=aAceFsB
set expandtab
set fileencodings=utf-8,chinese,latin-1,gb18030
set guifont=Ubuntu\ Mono\ 14
set guioptions=
set helplang=cn
set hlsearch
set imcmdline
set incsearch
set langmenu=zh_CN.UTF-8
set laststatus=2
set printoptions=paper:a4
set ruler
set runtimepath=~/.vim,~/.vim/bundle/taglist.vim,~/.vim/bundle/SuperTab,~/.vim/bundle/winmanager,~/.vim/bundle/c.vim,~/.vim/bundle/omnicppcomplete,~/.vim/bundle/YouCompleteMe,~/.vim/bundle/vimtips,~/.vim/bundle/powerline,~/.vim/bundle/nerdtree,/var/lib/vim/addons,/usr/share/vim/vimfiles,/usr/share/vim/vim74,/usr/share/vim/vimfiles/after,/var/lib/vim/addons/after,~/.vim/after,~/.vim/bundle/vundle/,~/.vim/bundle/taglist.vim/after,~/.vim/bundle/SuperTab/after,~/.vim/bundle/winmanager/after,~/.vim/bundle/c.vim/after,~/.vim/bundle/omnicppcomplete/after,~/.vim/bundle/YouCompleteMe/after,~/.vim/bundle/vimtips/after,~/.vim/bundle/powerline/after,~/.vim/bundle/nerdtree/after
set shiftwidth=4
set smartindent
set softtabstop=4
set suffixes=.bak,~,.swp,.o,.info,.aux,.log,.dvi,.bbl,.blg,.brf,.cb,.ind,.idx,.ilg,.inx,.out,.toc
set tabstop=4
set tags=tags,/usr/include/c++/4.8/tags,/usr/include/boost/tags,/usr/local/include/tags,~/example/python/Python-2.7.5/tags,~/Projects/VideoCapture/trunk/livebox/src/tags,/usr/local/lib/python2.7/tags,~/example/python/web/tags,~/.vim/ctags/CPP
set updatetime=2000
let s:so_save = &so | let s:siso_save = &siso | set so=0 siso=0
let v:this_session=expand("<sfile>:p")
silent only
cd ~/Projects/test/python/tornado/templates
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess=aoO
badd +0 ~/Projects/test/python/tornado/templates/munger_index.html
args munger_index.html
edit ~/Projects/test/python/tornado/templates/munger_index.html
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
argglobal
let s:cpo_save=&cpo
set cpo&vim
inoremap <buffer> <silent> <BS> =AutoPairsDelete()
inoremap <buffer> <silent> ­ =EchoFuncP()
inoremap <buffer> <silent> ½ =EchoFuncN()
inoremap <buffer> <silent> î :call AutoPairsJump()a
inoremap <buffer> <silent> <expr> ð AutoPairsToggle()
inoremap <buffer> <silent> â =AutoPairsBackInsert()
inoremap <buffer> <silent> å =AutoPairsFastWrap()
inoremap <buffer> <silent>  =AutoPairsDelete()
inoremap <buffer> <silent>   =AutoPairsSpace()
inoremap <buffer> <silent> " =AutoPairsInsert('"')
inoremap <buffer> <silent> ' =AutoPairsInsert('''')
inoremap <buffer> <silent> ( =AutoPairsInsert('(')
inoremap <buffer> <silent> ) =AutoPairsInsert(')')
noremap <buffer> <silent> î :call AutoPairsJump()
noremap <buffer> <silent> ð :call AutoPairsToggle()
inoremap <buffer> <silent> [ =AutoPairsInsert('[')
inoremap <buffer> <silent> ] =AutoPairsInsert(']')
inoremap <buffer> <silent> ` =AutoPairsInsert('`')
inoremap <buffer> <silent> { =AutoPairsInsert('{')
inoremap <buffer> <silent> } =AutoPairsInsert('}')
let &cpo=s:cpo_save
unlet s:cpo_save
setlocal keymap=
setlocal noarabic
setlocal autoindent
setlocal balloonexpr=
setlocal nobinary
setlocal bufhidden=
setlocal buflisted
setlocal buftype=
setlocal cindent
setlocal cinkeys=0{,0},0),:,0#,!^F,o,O,e
setlocal cinoptions=
setlocal cinwords=if,else,while,do,for,switch
setlocal colorcolumn=
setlocal comments=s:<!--,m:\ \ \ \ ,e:-->
setlocal commentstring=<!--%s-->
setlocal complete=.,w,b,u,t,i
setlocal concealcursor=
setlocal conceallevel=0
setlocal completefunc=youcompleteme#Complete
setlocal nocopyindent
setlocal cryptmethod=
setlocal nocursorbind
set cursorcolumn
setlocal cursorcolumn
setlocal nocursorline
setlocal define=
setlocal dictionary=
setlocal nodiff
setlocal equalprg=
setlocal errorformat=
setlocal expandtab
if &filetype != 'html'
setlocal filetype=html
endif
setlocal foldcolumn=0
setlocal foldenable
setlocal foldexpr=0
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldmarker={{{,}}}
set foldmethod=marker
setlocal foldmethod=marker
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldtext=foldtext()
setlocal formatexpr=
setlocal formatoptions=tcq
setlocal formatlistpat=^\\s*\\d\\+[\\]:.)}\\t\ ]\\s*
setlocal grepprg=
setlocal iminsert=2
setlocal imsearch=2
setlocal include=
setlocal includeexpr=
setlocal indentexpr=HtmlIndent()
setlocal indentkeys=o,O,<Return>,<>>,{,},!^F
setlocal noinfercase
setlocal iskeyword=@,48-57,_,192-255
setlocal keywordprg=
setlocal nolinebreak
setlocal nolisp
setlocal nolist
setlocal makeprg=
setlocal matchpairs=(:),{:},[:],<:>
setlocal modeline
setlocal modifiable
setlocal nrformats=octal,hex
set number
setlocal number
setlocal numberwidth=4
setlocal omnifunc=htmlcomplete#CompleteTags
setlocal path=
setlocal nopreserveindent
setlocal nopreviewwindow
setlocal quoteescape=\\
setlocal noreadonly
setlocal norelativenumber
setlocal norightleft
setlocal rightleftcmd=search
setlocal noscrollbind
setlocal shiftwidth=4
setlocal noshortname
setlocal smartindent
setlocal softtabstop=4
setlocal nospell
setlocal spellcapcheck=[.?!]\\_[\\])'\"\	\ ]\\+
setlocal spellfile=
setlocal spelllang=en
setlocal statusline=%!airline#statusline(1)
setlocal suffixesadd=
setlocal swapfile
setlocal synmaxcol=3000
if &syntax != 'html'
setlocal syntax=html
endif
setlocal tabstop=4
setlocal tags=
setlocal textwidth=0
setlocal thesaurus=
setlocal noundofile
setlocal nowinfixheight
setlocal nowinfixwidth
setlocal wrap
setlocal wrapmargin=0
let s:l = 6 - ((5 * winheight(0) + 23) / 46)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
6
normal! 0
tabnext 1
if exists('s:wipebuf')
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20 shortmess=filnxtToO
let s:sx = expand("<sfile>:p:r")."x.vim"
if file_readable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &so = s:so_save | let &siso = s:siso_save
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
