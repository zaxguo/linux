import os
import sys

ground_truth = "/home/liwei/ext4_orig.img"
ours = "/home/liwei/ext4_ours.img"
btt = "/home/liwei/btt"

def read_btt(btt_text):
    f = open(btt_text, 'r')
    btt = {}
    for line in f:
        tmp = line.split(',')
        vblk = tmp[0]
        pblk = tmp[-1]
        btt[int(vblk)] = int(pblk)
    return btt

def _compare(ground_truth_img, ours_img, vblk, pblk):
    ground_truth_img.seek(vblk << 9, 0)
    ours_img.seek(pblk << 9, 0)
    sector_truth = ground_truth_img.read(1 << 9)
    sector_ours  = ours_img.read(1 << 9)
    return sector_truth == sector_ours

def compare(ground_truth, ours, btt):
    ground_truth_img = open(ground_truth, 'rb')
    ours_img = open(ours, 'rb')
    for vblk in btt.keys():
        pblk = btt[vblk]
        if pblk == -1:
            continue
        res = _compare(ground_truth_img, ours_img, vblk, pblk)
        if res == False:
            print("diff found in logical block " + str(vblk))

btt = read_btt(btt)
compare(ground_truth, ours, btt)

