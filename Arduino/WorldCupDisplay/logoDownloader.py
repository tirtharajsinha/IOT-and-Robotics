import os
import requests
from pathlib import Path
from urllib.parse import urlparse
from PIL import Image
from io import BytesIO
import cairosvg

API_KEY = "1158ba1f4ca94d1ca0aa723f724cf677"

STANDINGS_URL = "https://api.football-data.org/v4/competitions/WC/standings?season=2026"

OUTPUT_DIR = Path("./data/logos")
OUTPUT_DIR.mkdir(parents=True, exist_ok=True)

HEADERS = {"X-Auth-Token": API_KEY}


def download_file(url):
    r = requests.get(url, timeout=30)
    r.raise_for_status()
    return r.content


def save_png(team_id, crest_url):
    try:
        print(f"Downloading {team_id} -> {crest_url}")

        data = download_file(crest_url)

        if crest_url.lower().endswith(".png"):

            output_file = OUTPUT_DIR / f"{team_id}.png"

            img = Image.open(BytesIO(data)).convert("RGBA")

            # Resize first (important)
            img.thumbnail((40, 40), Image.LANCZOS)

            # Create WHITE background (NOT transparent)
            canvas = Image.new("RGB", (40, 40), (255, 255, 255))

            # Paste using alpha mask
            canvas.paste(img, (0, 0), img)

            # Save FINAL as RGB (no alpha)
            canvas.save(output_file, optimize=True)

        elif crest_url.lower().endswith(".svg"):
            output_file = OUTPUT_DIR / f"{team_id}.png"

            cairosvg.svg2png(
                bytestring=data,
                write_to=str(output_file),
                output_width=40,
                output_height=40,
                background_color="white",
            )

            print(f"Converted SVG -> PNG: {output_file}")

        else:
            print(f"Unknown format: {crest_url}")

    except Exception as e:
        print(f"Failed for team {team_id}: {e}")


def get_teams():
    r = requests.get(STANDINGS_URL, headers=HEADERS, timeout=30)

    r.raise_for_status()

    data = r.json()

    teams = {}

    for standing in data.get("standings", []):
        for row in standing.get("table", []):

            team = row.get("team", {})

            team_id = team.get("id")
            crest = team.get("crest")

            if team_id and crest:
                teams[team_id] = crest

    return teams


def main():
    teams = get_teams()

    print(f"Found {len(teams)} teams")

    for team_id, crest_url in sorted(teams.items()):
        save_png(team_id, crest_url)

    print("Done")


if __name__ == "__main__":
    main()
