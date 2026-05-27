# PowerShell 파일 I/O

## BOM 없는 UTF-8로 쓰기

PowerShell에서 `[IO.File]::WriteAllText()` 또는 `Set-Content`를 사용할 때, 기본 `System.Text.Encoding.UTF8`은 **BOM을 포함**한다. Slidev(및 대부분의 웹 도구)는 BOM이 있으면 파일 첫 줄(`---`)을 프론트매터가 아닌 일반 텍스트로 인식해 렌더링 오류가 발생한다.

**항상 BOM 없는 UTF-8 인코딩을 명시한다.**

```powershell
# ✅ 올바른 방법 — BOM 없는 UTF-8
$utf8NoBom = New-Object System.Text.UTF8Encoding $false
[IO.File]::WriteAllText($path, $content, $utf8NoBom)

# ❌ 잘못된 방법 — BOM 포함됨
[IO.File]::WriteAllText($path, $content, [Text.Encoding]::UTF8)
[IO.File]::WriteAllText($path, $content)   # 기본값도 BOM 포함
```

이 규칙은 `.md`, `.json`, `.ts`, `.js`, `.vue` 등 **모든 텍스트 파일**에 적용한다.
