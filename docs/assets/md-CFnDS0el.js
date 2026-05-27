import{_ as r}from"./slidev/CodeBlockWrapper.vue_vue_type_script_setup_true_lang-CcCJ8bT7.js";import{o,b as u,w as a,g as s,D as n,d as c,m as d,v as f,x as m,z as e}from"./modules/vue-3CrVM1oy.js";import{I as g}from"./slidev/default-Czf27QD1.js";import{u as k,f as _}from"./slidev/context-5szJ5qQ6.js";import"./modules/unplugin-icons-BExRMqN9.js";import"./index-Bt03pUJS.js";import"./modules/shiki-B-6FJwZY.js";const w={__name:"io-buffers.md__slidev_199",setup(x){const{$clicksContext:t,$frontmatter:p}=k();return t.setup(),(b,l)=>{const i=r;return o(),u(g,f(m(e(_)(e(p),198))),{default:a(()=>[l[1]||(l[1]=s("h1",null,"파일 디스크립터 — 두 개의 레이어",-1)),l[2]||(l[2]=s("p",null,[n("C/C++ I/O는 "),s("strong",null,"유저 공간 레이어"),n("와 "),s("strong",null,"OS 레이어"),n(" 두 겹으로 이루어진다.")],-1)),c(i,d({},{title:"",ranges:[]}),{default:a(()=>[...l[0]||(l[0]=[s("pre",{class:"shiki shiki-themes vitesse-dark vitesse-light slidev-code",style:{"--shiki-dark":"#dbd7caee","--shiki-light":"#393a34","--shiki-dark-bg":"#121212","--shiki-light-bg":"#ffffff"}},[s("code",{class:"language-text"},[s("span",{class:"line"},[s("span",null,"┌──────────────────────────────────────────────────────────────┐")]),n(`
`),s("span",{class:"line"},[s("span",null,"│                      유저 공간 (User Space)                    │")]),n(`
`),s("span",{class:"line"},[s("span",null,"│                                                              │")]),n(`
`),s("span",{class:"line"},[s("span",null,"│  FILE* stdin   FILE* stdout   FILE* stderr                   │")]),n(`
`),s("span",{class:"line"},[s("span",null,"│  (유저 버퍼 포함)  (유저 버퍼 포함)  (버퍼 없음)                │")]),n(`
`),s("span",{class:"line"},[s("span",null,"│      │               │               │                       │")]),n(`
`),s("span",{class:"line"},[s("span",null,"│      └───────────────┼───────────────┘                       │")]),n(`
`),s("span",{class:"line"},[s("span",null,"│                      │  fread / fwrite / fprintf ...         │")]),n(`
`),s("span",{class:"line"},[s("span",null,"│                      ▼  (버퍼 가득 차거나 fflush 시)           │")]),n(`
`),s("span",{class:"line"},[s("span",null,"│                  [ 시스템 콜 ]                                 │")]),n(`
`),s("span",{class:"line"},[s("span",null,"├──────────────────────────────────────────────────────────────┤")]),n(`
`),s("span",{class:"line"},[s("span",null,"│                      OS 커널 (Kernel Space)                   │")]),n(`
`),s("span",{class:"line"},[s("span",null,"│                                                              │")]),n(`
`),s("span",{class:"line"},[s("span",null,"│   파일 디스크립터 테이블 (프로세스마다 존재)                      │")]),n(`
`),s("span",{class:"line"},[s("span",null,"│   FD 0 (stdin)  → 키보드 드라이버                              │")]),n(`
`),s("span",{class:"line"},[s("span",null,"│   FD 1 (stdout) → 터미널 드라이버 (또는 파일/파이프)             │")]),n(`
`),s("span",{class:"line"},[s("span",null,"│   FD 2 (stderr) → 터미널 드라이버 (또는 파일/파이프)             │")]),n(`
`),s("span",{class:"line"},[s("span",null,"└──────────────────────────────────────────────────────────────┘")])])],-1)])]),_:1},16),l[3]||(l[3]=s("blockquote",null,[s("p",null,[s("code",null,"FILE*"),n("은 파일 디스크립터(정수)를 "),s("strong",null,"감싼(wrap) 구조체"),n("다."),s("br"),n(" 유저 공간에서 버퍼를 관리하고, OS에 넘길 때만 시스템 콜을 호출한다.")])],-1))]),_:1},16)}}};export{w as default};
