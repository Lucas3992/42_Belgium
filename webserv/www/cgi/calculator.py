#!/usr/bin/env python3
import os
import sys

size_str = os.environ.get("CONTENT_LENGTH", "0")
size = int(size_str)
body = sys.stdin.read(size)
array = body.split("=")
if len(array) > 1:
    qt = int(array[1])
else:
    qt = 0

screws = qt * 37
ironing = qt * 23.25
ironore = qt * 23.25
ironrod = qt * 14.25
ironplt = qt * 6
rip = qt * 1
rotor = qt * 1

print("Content-Type: text/html\r")
print("\r")
print("""<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <link rel="stylesheet" href="/style.css">
    <title>FICSIT - Production Report</title>
    <style>
        body {
            min-height: 100vh;
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: flex-start;
            padding-top: 60px;
            margin: 0;
        }
        .container { max-width: 680px; width: 90%%; padding: 0 20px 60px; }
        .ficsit-header {
            display: flex;
            align-items: center;
            gap: 16px;
            margin-bottom: 32px;
            border-bottom: 2px solid #fa9414;
            padding-bottom: 16px;
        }
        .ficsit-logo { font-size: 28px; font-weight: 900; color: #fa9414; letter-spacing: 4px; text-transform: uppercase; }
        .ficsit-tagline { font-size: 11px; color: #888; letter-spacing: 2px; text-transform: uppercase; }
        .separator { width: 40px; height: 3px; background: #fa9414; margin: 0 0 28px; }
        .objective {
            background: #333;
            border-left: 5px solid #fa9414;
            padding: 12px 16px;
            margin-bottom: 24px;
            font-size: 14px;
            color: #ccc;
        }
        .objective span { color: #fa9414; font-weight: bold; font-size: 18px; }
        .result { margin-top: 8px; }
        .item {
            display: flex;
            justify-content: space-between;
            align-items: center;
            padding: 12px 16px;
            border-bottom: 1px solid #2a2a2a;
            font-size: 14px;
            color: #ccc;
        }
        .item:hover { background: #222; }
        .item .label { color: #888; text-transform: uppercase; font-size: 11px; letter-spacing: 1px; }
        .item .value { color: #fa9414; font-weight: bold; font-size: 15px; font-family: 'Courier New', monospace; }
        .section-title {
            font-size: 11px;
            text-transform: uppercase;
            letter-spacing: 2px;
            color: #fa9414;
            margin: 24px 0 8px;
            padding-bottom: 6px;
            border-bottom: 1px solid #333;
        }
        footer { margin-top: 40px; font-size: 11px; color: #444; text-transform: uppercase; letter-spacing: 2px; border-top: 1px solid #2a2a2a; padding-top: 16px; }
    </style>
</head>
<body>
    <div class="container">
        <div class="ficsit-header">
            <div>
                <div class="ficsit-logo">FICSIT Inc.</div>
                <div class="ficsit-tagline">Production Report — Smart Plating Module</div>
            </div>
        </div>

        <h1>Production Report</h1>
        <div class="separator"></div>
""")

print(f"""
        <div class="objective">
            Target output: <span>{qt}/min</span> Smart Platings
        </div>

        <div class="result">
            <div class="section-title">Raw Resources</div>
            <div class="item"><span class="label">Iron Ore</span><span class="value">{ironore}/min</span></div>

            <div class="section-title">Intermediate Parts</div>
            <div class="item"><span class="label">Iron Ingots</span><span class="value">{ironing}/min</span></div>
            <div class="item"><span class="label">Iron Rods</span><span class="value">{ironrod}/min</span></div>
            <div class="item"><span class="label">Screws</span><span class="value">{screws}/min</span></div>
            <div class="item"><span class="label">Iron Plates</span><span class="value">{ironplt}/min</span></div>

            <div class="section-title">Advanced Parts</div>
            <div class="item"><span class="label">Reinforced Iron Plates</span><span class="value">{rip}/min</span></div>
            <div class="item"><span class="label">Rotors</span><span class="value">{rotor}/min</span></div>
        </div>

        <br>
        <a href="/calculator.html" class="ficsit-btn">[ Back to Calculator ]</a>

        <footer>FICSIT Inc. — Waste nothing. Build everything.</footer>
    </div>
</body>
</html>
""")
