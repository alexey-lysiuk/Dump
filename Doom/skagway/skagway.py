
import os
import omg.mapedit


self_path = os.path.dirname(__file__)
self_path = os.path.abspath(self_path) + os.sep

os.chdir(self_path)

WAD_NAME = 'skagway.wad'

wad = omg.wad.WAD()
wad.from_file(WAD_NAME)

MAP_NAME = 'MAP01'

dmap = wad.maps[MAP_NAME]
editor = omg.mapedit.MapEditor(dmap)

# Remove damaging floors
# http://doomwiki.org/wiki/Sector

DAMAGE_SECTOR_TYPES = (
    4,  # 20% damage per second plus light blink 0.5 second
    5,  # 10% damage per second
    7,  # 5% damage per second
    16,  # 20% damage per second
)

# 32: 5% damage per second
# 64: 10% damage per second
# 96: 20% damage per second

DAMAGE_SECTOR_MASK = 96

for sector in editor.sectors:
    if sector.type in DAMAGE_SECTOR_TYPES:
        sector.type = 0
    else:
        sector.type &= ~DAMAGE_SECTOR_MASK

# Replace radiation suits with

thing_desc2num = omg.thinginfo.all_desc2num
radsuit_thing_type = thing_desc2num['radiation suit']
stimpack_thing_type = thing_desc2num['stimpack']

for thing in editor.things:
    if thing.type == radsuit_thing_type:
        thing.type = stimpack_thing_type

# Fix missing partial invisibility sphere on easy skill

invis_sphere = editor.things[566]
if invis_sphere.type == thing_desc2num['invisibility']:
    invis_sphere.easy = True

wad.maps[MAP_NAME] = editor.to_lumps()
wad.to_file(WAD_NAME)
