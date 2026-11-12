import os
from PIL import Image

output_dir = r"C:\IT\super_mario\src\ui\qt\resources\sprites"
os.makedirs(output_dir, exist_ok=True)

def create_sprite(filename, width, height, palette, pattern):
    img = Image.new("RGBA", (width, height), (0, 0, 0, 0))
    lines = [line.strip() for line in pattern.strip().split("\n") if line.strip()]
    for y in range(min(height, len(lines))):
        line = lines[y]
        for x in range(min(width, len(line))):
            char = line[x]
            if char in palette:
                img.putpixel((x, y), palette[char])
    img.save(os.path.join(output_dir, filename))
    print(f"Saved {filename}")

# 1. Mario (16x16)
mario_pal = {
    '.': (0, 0, 0, 0),
    'R': (228, 0, 88, 255),    # Red cap & shirt
    'S': (252, 160, 68, 255),   # Skin
    'B': (0, 88, 248, 255),     # Blue overalls
    'D': (104, 56, 0, 255),     # Dark brown hair & shoes
    'Y': (252, 224, 0, 255),    # Yellow buckle
    'K': (0, 0, 0, 255),        # Black eye
}
mario_pattern = """
....RRRRR.......
...RRRRRRRRR....
...DDDSSS.SK....
..DSDSSSDSSSS...
..DSDDDSSSDSS...
..DDSSSSDDDD....
....SSSSSSS.....
...RRBRRR.......
..RRRBRRBRRR....
.RRRRBBBBBRRR...
.SS.BYBBYB.SS...
.SSSBBBBBBSSS...
.SS.BBBBBB.SS...
...DDD..DDD.....
..DDDD..DDDD....
................
"""
create_sprite("mario.png", 16, 16, mario_pal, mario_pattern)

# 2. Goomba / Enemy (16x16)
goomba_pal = {
    '.': (0, 0, 0, 0),
    'C': (184, 72, 0, 255),     # Brown cap
    'S': (252, 216, 168, 255),  # Face
    'K': (0, 0, 0, 255),        # Black pupil & brow
    'W': (255, 255, 255, 255),  # White eye
    'F': (72, 40, 0, 255),      # Dark feet
}
goomba_pattern = """
......CCCC......
....CCCCCCCC....
...CCCCCCCCCC...
..CCCCCCCCCCCC..
.CCCCCCCCCCCCCC.
.CCKCCCCCCCCKCC.
.CKKCCCCCCCCKKC.
.CKWWCCCCCCWWKC.
.CKKWKCCCCKWKKC.
..SSWWSSSSWWSS..
...SSSSSSSSSS...
...SSSSSSSSSS...
...SSSSSSSSSS...
..FFF......FFF..
.FFFFF....FFFFF.
.FFFFF....FFFFF.
"""
create_sprite("enemy.png", 16, 16, goomba_pal, goomba_pattern)

# 3. Flying Enemy (16x16)
flying_pal = {
    '.': (0, 0, 0, 0),
    'C': (184, 72, 0, 255),
    'S': (252, 216, 168, 255),
    'K': (0, 0, 0, 255),
    'W': (255, 255, 255, 255),
    'F': (72, 40, 0, 255),
    'B': (100, 160, 255, 255),  # Wing shade
}
flying_pattern = """
...WW....WW.....
..WWBW..WWBW....
.WW..CCCC..WW...
.W.CCCCCCCC.W...
..CCCCCCCCCC....
.CCCCCCCCCCCC...
.CCKCCCCCCCCKCC.
.CKKCCCCCCCCKKC.
.CKWWCCCCCCWWKC.
.CKKWKCCCCKWKKC.
..SSWWSSSSWWSS..
...SSSSSSSSSS...
...SSSSSSSSSS...
..FFF......FFF..
.FFFFF....FFFFF.
................
"""
create_sprite("flying_enemy.png", 16, 16, flying_pal, flying_pattern)

# 4. Jumping Enemy (16x16)
jumping_pal = {
    '.': (0, 0, 0, 0),
    'C': (0, 168, 0, 255),      # Green cap
    'S': (252, 216, 168, 255),
    'K': (0, 0, 0, 255),
    'W': (255, 255, 255, 255),
    'F': (184, 72, 0, 255),
}
jumping_pattern = """
......CCCC......
....CCCCCCCC....
...CCCCCCCCCC...
..CCCCCCCCCCCC..
.CCCCCCCCCCCCCC.
.CCKCCCCCCCCKCC.
.CKKCCCCCCCCKKC.
.CKWWCCCCCCWWKC.
.CKKWKCCCCKWKKC.
..SSWWSSSSWWSS..
...SSSSSSSSSS...
...SSSSSSSSSS...
..FFF......FFF..
.FFFFF....FFFFF.
.FFFF......FFFF.
................
"""
create_sprite("jumping_enemy.png", 16, 16, jumping_pal, jumping_pattern)

# 5. Brick (Box) (16x16)
brick_pal = {
    'O': (200, 76, 12, 255),
    'L': (248, 148, 56, 255),
    'D': (0, 0, 0, 255),
}
brick_pattern = """
LLLLLLLLLLLLLLLD
LOOOOOODLOOOOOOD
LOOOOOODLOOOOOOD
DDDDDDDDDDDDDDDD
LLLLLLLDLLLLLLLD
LOOOOOODLOOOOOOD
LOOOOOODLOOOOOOD
DDDDDDDDDDDDDDDD
LLLLLLLLLLLLLLLD
LOOOOOODLOOOOOOD
LOOOOOODLOOOOOOD
DDDDDDDDDDDDDDDD
LLLLLLLDLLLLLLLD
LOOOOOODLOOOOOOD
LOOOOOODLOOOOOOD
DDDDDDDDDDDDDDDD
"""
create_sprite("box.png", 16, 16, brick_pal, brick_pattern)

# 6. Question Block (FullBox - Active) (16x16)
qbox_pal = {
    'G': (252, 160, 16, 255),
    'L': (252, 224, 112, 255),
    'D': (136, 48, 0, 255),
    'K': (0, 0, 0, 255),
    'W': (255, 255, 255, 255),
}
qbox_pattern = """
DDDDDDDDDDDDDDDD
DLLLLLLLLLLLLLLK
DLKKKKKKKKKKKKDK
DLKGGGGGGGGGGKDK
DLKGWWWWWWWGGKDK
DLKGWGGGGGWGGKDK
DLKGGGGGGGWGGKDK
DLKGGGGGGWWGGKDK
DLKGGGGWWGGGGKDK
DLKGGGGWWGGGGKDK
DLKGGGGGGGGGGKDK
DLKGGGGWWGGGGKDK
DLKGGGGWWGGGGKDK
DLKGGGGGGGGGGKDK
DLKKKKKKKKKKKKDK
DKKKKKKKKKKKKKKK
"""
create_sprite("full_box.png", 16, 16, qbox_pal, qbox_pattern)

# 7. Empty Block (FullBox - Inactive) (16x16)
empty_pal = {
    'L': (180, 130, 90, 255),
    'D': (100, 60, 30, 255),
    'K': (0, 0, 0, 255),
}
empty_pattern = """
DDDDDDDDDDDDDDDD
DLLLLLLLLLLLLLLK
DLKDDDDDDDDDDKDK
DLDKDDDDDDDDKDDK
DLDDKDDDDDDKDDDK
DLDDDKDDDDDKDDDK
DLDDDDDDDDDDDDDK
DLDDDDDDDDDDDDDK
DLDDDDDDDDDDDDDK
DLDDDDDDDDDDDDDK
DLDDDKDDDDDKDDDK
DLDDKDDDDDDKDDDK
DLDKDDDDDDDDKDDK
DLKDDDDDDDDDDKDK
DLKKKKKKKKKKKKDK
DKKKKKKKKKKKKKKK
"""
create_sprite("empty_box.png", 16, 16, empty_pal, empty_pattern)

# 8. Ground Top (Ship top) (16x16)
gtop_pal = {
    'G': (0, 168, 0, 255),      # Green grass
    'g': (128, 208, 16, 255),   # Light green grass
    'C': (200, 76, 12, 255),    # Soil
    'D': (104, 32, 0, 255),     # Dark soil
}
gtop_pattern = """
GGGGGGGGGGGGGGGG
GGGGGGGGGGGGGGGG
GgGggGgGGggGgGgG
CCCCCCCCCCCCCCCC
CDDDCCCDDDCCCDDC
CDDDCCCDDDCCCDDC
CCCCCCCCCCCCCCCC
CCCDDDCCCDDDCCCC
CCCDDDCCCDDDCCCC
CCCCCCCCCCCCCCCC
CDDDCCCDDDCCCDDC
CDDDCCCDDDCCCDDC
CCCCCCCCCCCCCCCC
CCCDDDCCCDDDCCCC
CCCDDDCCCDDDCCCC
DDDDDDDDDDDDDDDD
"""
create_sprite("ground_top.png", 16, 16, gtop_pal, gtop_pattern)

# 9. Ground Sub (Ship bottom) (16x16)
gsub_pal = {
    'C': (200, 76, 12, 255),
    'D': (104, 32, 0, 255),
}
gsub_pattern = """
CCCCCCCCCCCCCCCC
CDDDCCCDDDCCCDDC
CDDDCCCDDDCCCDDC
CCCCCCCCCCCCCCCC
CCCDDDCCCDDDCCCC
CCCDDDCCCDDDCCCC
CCCCCCCCCCCCCCCC
CDDDCCCDDDCCCDDC
CDDDCCCDDDCCCDDC
CCCCCCCCCCCCCCCC
CCCDDDCCCDDDCCCC
CCCDDDCCCDDDCCCC
CCCCCCCCCCCCCCCC
CDDDCCCDDDCCCDDC
CDDDCCCDDDCCCDDC
DDDDDDDDDDDDDDDD
"""
create_sprite("ground_sub.png", 16, 16, gsub_pal, gsub_pattern)

# 10. Coin (Money) (16x16)
coin_pal = {
    '.': (0, 0, 0, 0),
    'D': (160, 96, 0, 255),
    'Y': (252, 216, 0, 255),
    'W': (255, 255, 255, 255),
    'K': (120, 60, 0, 255),
}
coin_pattern = """
......DDDD......
....DDYYYYDD....
...DYYYYYYYYD...
..DYYYWKYYYYYD..
..DYYYWKYYYYYD..
.DYYYYWKYYYYYYD.
.DYYYYWKYYYYYYD.
.DYYYYWKYYYYYYD.
.DYYYYWKYYYYYYD.
.DYYYYWKYYYYYYD.
.DYYYYWKYYYYYYD.
..DYYYWKYYYYYD..
..DYYYWKYYYYYD..
...DYYYYYYYYD...
....DDYYYYDD....
......DDDD......
"""
create_sprite("money.png", 16, 16, coin_pal, coin_pattern)

# 11. Moving Platform (16x16)
platform_pal = {
    'O': (248, 120, 32, 255),   # Orange wood
    'L': (252, 188, 112, 255),  # Light wood
    'D': (136, 48, 0, 255),     # Dark edge
    'W': (255, 255, 255, 255),  # White trim
}
platform_pattern = """
WWWWWWWWWWWWWWWW
LLLLLLLLLLLLLLLL
LOOOOOOOOOOOOOOD
LOOOOOOOOOOOOOOD
LDDDDDDDDDDDDDDD
LOOOOOOOOOOOOOOD
LOOOOOOOOOOOOOOD
LOOOOOOOOOOOOOOD
LDDDDDDDDDDDDDDD
LOOOOOOOOOOOOOOD
LOOOOOOOOOOOOOOD
LOOOOOOOOOOOOOOD
LDDDDDDDDDDDDDDD
LOOOOOOOOOOOOOOD
LOOOOOOOOOOOOOOD
DDDDDDDDDDDDDDDD
"""
create_sprite("moving_platform.png", 16, 16, platform_pal, platform_pattern)

# 12. Finish (32x32 - Castle/Goal)
finish_img = Image.new("RGBA", (32, 32), (0, 0, 0, 0))
# Let's draw castle bricks & pole
F_BRICK = (184, 72, 0, 255)
F_DARK = (0, 0, 0, 255)
F_WHITE = (255, 255, 255, 255)
F_GREEN = (0, 168, 0, 255)
F_POLE = (128, 128, 128, 255)

# Flag pole & flag on top
for y in range(0, 32):
    finish_img.putpixel((6, y), F_POLE)
    finish_img.putpixel((7, y), F_POLE)
# Green ball on top
for x in range(5, 9):
    for y in range(0, 4):
        finish_img.putpixel((x, y), F_GREEN)
# White/Green triangle flag
for y in range(4, 14):
    for x in range(8, 8 + (14 - y)):
        finish_img.putpixel((x, y), F_WHITE if (x + y) % 2 == 0 else F_GREEN)

# Small castle base at the right (x: 12..31, y: 12..31)
for y in range(12, 32):
    for x in range(12, 32):
        if (x in (12, 31) or y in (12, 31) or y % 5 == 0 or (x % 5 == 0 and (y // 5) % 2 == 0)):
            finish_img.putpixel((x, y), F_DARK)
        else:
            finish_img.putpixel((x, y), F_BRICK)
# Castle door (x: 18..25, y: 22..31)
for y in range(22, 32):
    for x in range(19, 25):
        finish_img.putpixel((x, y), (0, 0, 0, 255))
# Castle battlements (y: 8..11)
for bx in [12, 13, 17, 18, 22, 23, 27, 28, 30, 31]:
    for by in range(8, 12):
        finish_img.putpixel((bx, by), F_BRICK)

finish_img.save(os.path.join(output_dir, "finish.png"))
print("Saved finish.png")

print("All sprites successfully generated!")
