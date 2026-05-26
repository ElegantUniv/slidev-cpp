import{_ as r}from"./slidev/CodeBlockWrapper.vue_vue_type_script_setup_true_lang-C1nI2JJb.js";import{o as i,b as c,w as a,g as l,D as n,d,m,v as f,x as g,z as t}from"./modules/vue-3CrVM1oy.js";import{I as k}from"./slidev/two-cols-header-z1fw6kjp.js";import{u as _,f as h}from"./slidev/context-q57BfsuZ.js";import"./modules/unplugin-icons-BExRMqN9.js";import"./index-CA1WcYih.js";import"./modules/shiki-B-6FJwZY.js";const H={__name:"c-memory.md__slidev_95",setup(x){const{$clicksContext:e,$frontmatter:p}=_();return e.setup(),(b,s)=>{const u=r;return i(),c(k,f(g(t(h)(t(p),94))),{left:a(o=>[d(u,m({},{title:"",ranges:[]}),{default:a(()=>[...s[0]||(s[0]=[l("pre",{class:"shiki shiki-themes vitesse-dark vitesse-light slidev-code",style:{"--shiki-dark":"#dbd7caee","--shiki-light":"#393a34","--shiki-dark-bg":"#121212","--shiki-light-bg":"#ffffff"}},[l("code",{class:"language-text"},[l("span",{class:"line"},[l("span",null,"높은 주소")]),n(`
`),l("span",{class:"line"},[l("span",null,"┌─────────────────────────┐")]),n(`
`),l("span",{class:"line"},[l("span",null,"│        Stack            │  ← 지역 변수, 함수 호출")]),n(`
`),l("span",{class:"line"},[l("span",null,"│   (위에서 아래로 성장)     │     자동 할당 / 자동 해제")]),n(`
`),l("span",{class:"line"},[l("span",null,"├─────────────────────────┤")]),n(`
`),l("span",{class:"line"},[l("span",null,"│           ↕             │")]),n(`
`),l("span",{class:"line"},[l("span",null,"│        (여유 공간)        │")]),n(`
`),l("span",{class:"line"},[l("span",null,"│           ↕             │")]),n(`
`),l("span",{class:"line"},[l("span",null,"├─────────────────────────┤")]),n(`
`),l("span",{class:"line"},[l("span",null,"│         Heap            │  ← 동적 메모리")]),n(`
`),l("span",{class:"line"},[l("span",null,"│   (아래에서 위로 성장)      │     malloc() / free()")]),n(`
`),l("span",{class:"line"},[l("span",null,"├─────────────────────────┤")]),n(`
`),l("span",{class:"line"},[l("span",null,"│    BSS (미초기화)        │  ← 초기화 안 된 전역변수")]),n(`
`),l("span",{class:"line"},[l("span",null,"├─────────────────────────┤")]),n(`
`),l("span",{class:"line"},[l("span",null,"│    Data (초기화됨)       │  ← 초기화된 전역/정적 변수")]),n(`
`),l("span",{class:"line"},[l("span",null,"├─────────────────────────┤")]),n(`
`),l("span",{class:"line"},[l("span",null,"│    Text (Code)          │  ← 실행 코드 (읽기 전용)")]),n(`
`),l("span",{class:"line"},[l("span",null,"└─────────────────────────┘")]),n(`
`),l("span",{class:"line"},[l("span",null,"낮은 주소")])])],-1)])]),_:1},16)]),right:a(o=>[...s[1]||(s[1]=[l("table",null,[l("thead",null,[l("tr",null,[l("th",null,"영역"),l("th",null,"설명")])]),l("tbody",null,[l("tr",null,[l("td",null,[l("strong",null,"코드(Code)")]),l("td",null,"실행할 기계어 명령이 저장되는 영역")]),l("tr",null,[l("td",null,[l("strong",null,"데이터(Data)")]),l("td",null,"전역 변수, 정적 변수가 저장되는 영역")]),l("tr",null,[l("td",null,[l("strong",null,"스택(Stack)")]),l("td",null,"함수 호출 시 지역 변수·매개변수가 저장되는 영역 (자동 관리)")]),l("tr",null,[l("td",null,[l("strong",null,"힙(Heap)")]),l("td",null,"프로그래머가 직접 할당·해제하는 영역 (동적 할당)")])])],-1),l("br",null,null,-1),l("blockquote",null,[l("p",null,[n("동적 메모리 할당은 "),l("strong",null,"힙(Heap)"),n(" 영역을 사용한다.")])],-1)])]),default:a(()=>[s[2]||(s[2]=l("h1",null,"프로그램의 메모리 구조",-1)),s[3]||(s[3]=l("p",null,"프로그램 실행 시 메모리는 크게 4개의 영역으로 나뉜다.",-1))]),_:1},16)}}};export{H as default};
