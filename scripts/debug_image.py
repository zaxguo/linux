import os
import sys

ground_truth = "~/ext4.img"
ours = "~/ext4_ours.img"
btt = "~/btt.log"

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
    sector_truth = ground_truth_img.seek(vblk << 9, 0).read(1 << 9)
    sector_ours = ours_img.seek(pblk << 9, 0).read(1 << 9)
    return sector_truth == sector_ours

def compare(ground_truth, ours, btt):
    ground_truth_img = open(ground_truth, 'rb')
    ours_img = open(ours, 'rb')
    for sector in btt.keys():
        res = _compare(ground_truth_img, ours_img, sector, btt[sector])
        if res == False:
            print("diff sector found!!!")


