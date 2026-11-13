# Verify thinBasic_ZeroMQ.dll: PE i386, exports, VERSIONINFO.
param(
    [Parameter(Mandatory = $true)]
    [string] $DllPath,
    [string] $Objdump = "",
    [string] $ExpectedFileDescription = "ThinBasic ZeroMQ SDK module",
    [string] $ExpectedProductVersion = "0.1.0.0",
    [string] $ExpectedCompanyName = "Ji-Feng Tsai",
    [string] $ExpectedProductName = "ThinBasicZMQ",
    [string] $ExpectedOriginalFilename = "thinBasic_ZeroMQ.dll"
)

$ErrorActionPreference = "Stop"
$DllPath = [IO.Path]::GetFullPath($DllPath)

if (-not (Test-Path -LiteralPath $DllPath)) {
    throw "DLL not found: $DllPath"
}

$fs = [IO.File]::OpenRead($DllPath)
try {
    $br = New-Object IO.BinaryReader $fs
    $fs.Position = 0x3C
    $pe = $br.ReadInt32()
    $fs.Position = $pe
    $sig = [Text.Encoding]::ASCII.GetString($br.ReadBytes(4))
    if ($sig -ne "PE`0`0") {
        throw "Not a PE file (signature='$sig')"
    }

    $machine = $br.ReadUInt16()
    if ($machine -ne 0x14C) {
        throw "PE machine is 0x$($machine.ToString('X4')); expected i386 (0x14C)"
    }

    Write-Host "PE machine: i386 (0x14C)"
}
finally {
    $fs.Dispose()
}

$vi = (Get-Item -LiteralPath $DllPath).VersionInfo

function Assert-VersionField {
    param(
        [string] $Name,
        [string] $Actual,
        [string] $Expected
    )

    $actualTrim = if ($null -eq $Actual) { "" } else { $Actual.Trim() }
    $expectedTrim = if ($null -eq $Expected) { "" } else { $Expected.Trim() }

    if ([string]::IsNullOrWhiteSpace($actualTrim)) {
        throw "VERSIONINFO $Name is empty"
    }

    if ($actualTrim -ne $expectedTrim) {
        throw "VERSIONINFO $Name mismatch: expected '$expectedTrim', got '$actualTrim'"
    }

    Write-Host "VERSIONINFO OK: $Name = $actualTrim"
}

Assert-VersionField -Name "FileDescription" -Actual $vi.FileDescription -Expected $ExpectedFileDescription
Assert-VersionField -Name "ProductVersion" -Actual $vi.ProductVersion -Expected $ExpectedProductVersion
Assert-VersionField -Name "FileVersion" -Actual $vi.FileVersion -Expected $ExpectedProductVersion
Assert-VersionField -Name "CompanyName" -Actual $vi.CompanyName -Expected $ExpectedCompanyName
Assert-VersionField -Name "ProductName" -Actual $vi.ProductName -Expected $ExpectedProductName
Assert-VersionField -Name "OriginalFilename" -Actual $vi.OriginalFilename -Expected $ExpectedOriginalFilename

$dumpExe = $null
if ($Objdump -and (Test-Path -LiteralPath $Objdump)) {
    $dumpExe = $Objdump
}
elseif (Get-Command objdump.exe -ErrorAction SilentlyContinue) {
    $dumpExe = (Get-Command objdump.exe).Source
}

if (-not $dumpExe) {
    throw "objdump not found; export check required"
}

$dump = & $dumpExe -p $DllPath 2>&1 | Out-String
$required = @("_LoadLocalSymbols", "_UnLoadLocalSymbols")
foreach ($name in $required) {
    if ($dump -notmatch [regex]::Escape($name)) {
        throw "Missing export: $name"
    }
    Write-Host "Export OK: $name"
}

Write-Host "DLL checks passed: $DllPath"
