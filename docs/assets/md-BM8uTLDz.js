import{_ as p}from"./slidev/CodeBlockWrapper.vue_vue_type_script_setup_true_lang-CmGP9OY7.js";import{o as i,b as o,w as a,g as l,d,m as c,D as n,v as m,x as _,z as e}from"./modules/vue-3CrVM1oy.js";import{I as f}from"./slidev/default-BDtIUPvm.js";import{u as k,f as h}from"./slidev/context-D5RKgiOA.js";import"./modules/unplugin-icons-BExRMqN9.js";import"./index-BRpgbF9k.js";import"./modules/shiki-B-6FJwZY.js";const P={__name:"cpp-smart-pointer.md__slidev_177",setup(g){const{$clicksContext:t,$frontmatter:r}=k();return t.setup(),(b,s)=>{const u=p;return i(),o(f,m(_(e(h)(e(r),176))),{default:a(()=>[s[1]||(s[1]=l("h1",null,"스마트 포인터 선택 가이드",-1)),d(u,c({},{title:"",ranges:[]}),{default:a(()=>[...s[0]||(s[0]=[l("pre",{class:"shiki shiki-themes vitesse-dark vitesse-light slidev-code",style:{"--shiki-dark":"#dbd7caee","--shiki-light":"#393a34","--shiki-dark-bg":"#121212","--shiki-light-bg":"#ffffff"}},[l("code",{class:"language-text"},[l("span",{class:"line"},[l("span",null,"동적 할당이 필요한가?")]),n(`
`),l("span",{class:"line"},[l("span",null,"│")]),n(`
`),l("span",{class:"line"},[l("span",null,"├─ 단독 소유 (기본 선택)")]),n(`
`),l("span",{class:"line"},[l("span",null,"│      → unique_ptr<T>")]),n(`
`),l("span",{class:"line"},[l("span",null,"│        make_unique<T>(args...)")]),n(`
`),l("span",{class:"line"},[l("span",null,"│")]),n(`
`),l("span",{class:"line"},[l("span",null,"├─ 여러 곳에서 공유해야 하는가?")]),n(`
`),l("span",{class:"line"},[l("span",null,"│      → shared_ptr<T>")]),n(`
`),l("span",{class:"line"},[l("span",null,"│        make_shared<T>(args...)")]),n(`
`),l("span",{class:"line"},[l("span",null,"│")]),n(`
`),l("span",{class:"line"},[l("span",null,"│        shared_ptr를 쓰는데 순환 참조가 생기는가?")]),n(`
`),l("span",{class:"line"},[l("span",null,"│            → 한쪽을 weak_ptr<T>로 변경")]),n(`
`),l("span",{class:"line"},[l("span",null,"│")]),n(`
`),l("span",{class:"line"},[l("span",null,"└─ 이미 존재하는 C 자원 (FILE*, malloc 등)?")]),n(`
`),l("span",{class:"line"},[l("span",null,"       → unique_ptr / shared_ptr + 커스텀 삭제자")])])],-1)])]),_:1},16),s[2]||(s[2]=l("br",null,null,-1)),s[3]||(s[3]=l("table",null,[l("thead",null,[l("tr",null,[l("th",null,"상황"),l("th",null,"선택")])]),l("tbody",null,[l("tr",null,[l("td",null,"함수 내 지역 동적 할당"),l("td",null,[l("code",null,"unique_ptr")])]),l("tr",null,[l("td",null,"팩토리 함수 반환값"),l("td",null,[l("code",null,"unique_ptr")])]),l("tr",null,[l("td",null,"컨테이너에 다형성 객체 저장"),l("td",null,[l("code",null,"vector<unique_ptr<Base>>")])]),l("tr",null,[l("td",null,"캐시, 공유 설정 객체"),l("td",null,[l("code",null,"shared_ptr")])]),l("tr",null,[l("td",null,"부모↔자식 양방향 참조"),l("td",null,[n("부모→자식 "),l("code",null,"shared_ptr"),n(", 자식→부모 "),l("code",null,"weak_ptr")])]),l("tr",null,[l("td",null,"관찰자(Observer) 패턴"),l("td",null,[l("code",null,"weak_ptr")])])])],-1))]),_:1},16)}}};export{P as default};
