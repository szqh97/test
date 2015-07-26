#!/usr/bin/env python
"""
this scripts is used for insight midiated data generating
"""
import pandas as pd
import numpy as np

import sys
import os

def usage():
    """
    xx_sample_site_info.csv is a file like :
    ckingWebsite_id,view_count,cr,pageview_percentage,daily_global_pageview
    1,19966,0.88,2.392812672%,90562000000
    11,14782,0.88,0.025509119%,90562000000
    136,9,0.88,0.026921932%,90562000000
    150,10880,0.88,0.0003546493%,90562000000
    """
    info = "new_sample_site_info.csv old_sample_site_info.csv \
            matched_videos.csv arch_matched_videos.csv"
    print 'usage: ', sys.argv[0], info

usage()

#new_sample_site_info = pd.read_csv(sys.argv[1])
#old_sample_site_info = pd.read_csv(sys.argv[2])

new_dailySiteViewBasic = pd.read_csv('./new_dailySiteViewsBasic.csv')
old_dailySiteViewBasic = pd.read_csv('./old_dailySiteViewsBasic.csv')

new_dailySiteViewBasic['pageview_percent'] = new_dailySiteViewBasic.pageview_percentage/100.0
new_dailySiteViewBasic['daily_global_pageview'] = 90562000000
old_dailySiteViewBasic['pageview_percent'] = old_dailySiteViewBasic.pageview_percentage/100.0
old_dailySiteViewBasic['daily_global_pageview'] = 109000000000


def new_title_based_piracy(new_sample_site_info):
    """
    generating title based piracy for new consumption
    """
    #global new_sample_site_info
    new_sample_site_info['pageview_percent'] = \
            new_sample_site_info.pageview_percentage.apply(lambda x: \
            float(x.replace('%', ''))/100.0)
    new_sample_site_info['title_based_piracy'] = \
            new_sample_site_info.view_count/(new_sample_site_info.daily_global_pageview * \
            new_sample_site_info.cr * new_sample_site_info.pageview_percent)

    if len(new_sample_site_info) > 5:
        new_sample_site_info = new_sample_site_info.sort(columns='title_based_piracy')[1:-1]


    avg_title_based_piracy = (new_sample_site_info.view_count * \
            new_sample_site_info.title_based_piracy).sum()/new_sample_site_info.view_count.sum()
    return avg_title_based_piracy

def old_title_based_piracy(old_sample_site_info, estimated_site_match):
    """
    generating title_based_piracy for old consumtion
    """
    #global old_sample_site_info
    old_sample_site_info['pageview_percent'] = \
            old_sample_site_info.pageview_percentage.apply(lambda x: \
            float(x.replace('%', '')) / 100.0)
    old_sample_site_info['title_based_piracy'] = \
            old_sample_site_info.view_count/(old_sample_site_info.daily_global_pageview * \
            old_sample_site_info.cr * old_sample_site_info.pageview_percent)

    tmp_pd = old_sample_site_info.copy()
    tmp_pd.matches = abs(tmp_pd.matches - estimated_site_match)

    avg_title_based_piracy = np.average(tmp_pd.title_based_piracy)
    if len(old_sample_site_info) > 6:
        tmp_pd = tmp_pd.sort(columns='matches')
        avg_title_based_piracy = np.average(tmp_pd[0:5].title_based_piracy)
    return avg_title_based_piracy


def merge_matched_videos(matchedvideos, arch_matchedvideos):
    """
    merge matched viedeos and arch matched viedeos:w
    """
    #tmp_m = matchedvideos.append(arch_matchedvideos, on='trackingWebsite_id')
    tmp_m = matchedvideos.append(arch_matchedvideos)
    tmp_group = tmp_m.groupby('trackingWebsite_id')
    merged_matchedvideos = pd.concat([tmp_group.website_type.all(), \
            tmp_group.matches.sum()], axis=1)
    merged_matchedvideos['trackingWebsite_id'] = merged_matchedvideos.index
    return merged_matchedvideos


def gen_new_mediated_data(new_sample_site_info_table, matched_videos_table, \
        arch_matched_videos_table, meta_id):
    """
    gen new mediated data
    """
    pd_new_sample_site_info = pd.read_table(new_sample_site_info_table)
    pd_arch_matched_videos = None
    pd_matched_videos = None
    pd_merged_matched_videos = None
    if matched_videos_table == None or arch_matched_videos_table == None:
        if arch_matched_videos_table != None:
            pd_arch_matched_videos = pd.read_table(arch_matched_videos_table)
            pd_merged_matched_videos = pd_arch_matched_videos
        else:
            pd_matched_videos = pd.read_table(matched_videos_table)
            pd_merged_matched_videos = pd_matched_videos

    else:
        pd_matched_videos = pd.read_table(matched_videos_table)
        pd_arch_matched_videos = pd.read_table(arch_matched_videos_table)
        pd_merged_matched_videos = merge_matched_videos(pd_matched_videos, pd_arch_matched_videos)

    pd_merged_matched_videos = pd_merged_matched_videos.merge(new_dailySiteViewBasic, \
            on='trackingWebsite_id')
    # in new comsuption model all website use just one title_based_piracy
    avg_title_based_piracy = new_title_based_piracy(pd_new_sample_site_info)
    pd_merged_matched_videos['title_based_piracy'] = avg_title_based_piracy
    pd_merged_matched_videos['trackingMeta_id'] = meta_id
    return pd_merged_matched_videos.query("website_type in ('ugc', 'hybrid')")

def gen_old_mediated_data(old_sample_site_info_table, matched_videos_table, \
        arch_matched_videos_table, meta_id):
    """
    gen old mediated data
    """
    pd_old_sample_site_info = pd.read_table(old_sample_site_info_table)
    #pd_matched_videos = pd.read_table(matched_videos_table)
    pd_matched_videos = None
    pd_arch_matched_videos = None
    pd_merged_matched_videos = None
    if matched_videos_table == None or arch_matched_videos_table == None:
        if arch_matched_videos_table != None:
            pd_arch_matched_videos = pd.read_table(arch_matched_videos_table)
            pd_merged_matched_videos = pd_arch_matched_videos
        else:
            pd_matched_videos = pd.read_table(matched_videos_table)
            pd_merged_matched_videos = pd_matched_videos

    else:
        pd_matched_videos = pd.read_table(matched_videos_table)
        pd_arch_matched_videos = pd.read_table(arch_matched_videos_table)
        pd_merged_matched_videos = merge_matched_videos(pd_matched_videos, pd_arch_matched_videos)
    pd_merged_matched_videos = pd_merged_matched_videos.merge(old_dailySiteViewBasic, \
            on='trackingWebsite_id')

    def lambda_old_title_based_piracy(matches):
        """ this is only used for DataFrame.apply"""
        return old_title_based_piracy(pd_old_sample_site_info, matches)

    pd_merged_matched_videos['title_based_piracy'] = \
            pd_merged_matched_videos.matches.apply(lambda_old_title_based_piracy)
    pd_merged_matched_videos['trackingMeta_id'] = meta_id
    return pd_merged_matched_videos.query("website_type in ('ugc', 'hybrid')")





def main_func():
    """
    then entrence for main
    """
    tracking_meta_files = './trackingMetas.txt'
    new_mediated_data_file = 'new_consumption_file.csv'
    old_mediated_data_file = 'old_consumption_file.csv'
    header = "website_type,trackingWebsite_id,matches,cr,pageview_percentage,pageview_percent,\
            daily_global_pageview,title_based_piracy,meta_id\n"
    with file(new_mediated_data_file, 'a') as new_mediated_data_file_fd:
        new_mediated_data_file_fd.write(header)
    with file(old_mediated_data_file, 'a') as old_mediated_data_file_fd:
        old_mediated_data_file_fd.write(header)
    with file(tracking_meta_files, 'r') as trackingMetas_fd:
        meta_id = trackingMetas_fd.readline().replace('\n', '')
        while len(meta_id) != 0:
            print 'meta_id is ', meta_id
            new_sample_site_info_table = './data/' + meta_id +'_new_sample_site_info.csv'
            old_sample_site_info_table = './data/' + meta_id +'_old_sample_site_info.csv'
            matched_videos_table = './data/' + meta_id + '_matchedVideo_matches.csv'
            arch_matched_videos_table = './data/' + meta_id + '_arch_matchedVideo_matches.csv'
            if not os.path.exists(new_sample_site_info_table) and \
                   os.path.exists(old_sample_site_info_table) and \
                   os.path.exists(matched_videos_table) and \
                   os.path.exists(arch_matched_videos_table):
                print >> sys.stderr, meta_id, " files errror!"
                meta_id = trackingMetas_fd.readline().replace('\n', '')
                continue
            if os.stat(new_sample_site_info_table).st_size == 0 or \
                    os.stat(old_sample_site_info_table).st_size == 0:
                print >> sys.stdout, meta_id, " no sample files"
                meta_id = trackingMetas_fd.readline().replace('\n', '')
                continue
            if os.stat(matched_videos_table).st_size == 0 and \
                    os.stat(arch_matched_videos_table).st_size == 0:
                print >> sys.stdout, meta_id, " only report views"
                meta_id = trackingMetas_fd.readline().replace('\n', '')
                continue
            if os.stat(arch_matched_videos_table).st_size == 0:
                arch_matched_videos_table = None

            if os.stat(matched_videos_table).st_size == 0:
                matched_videos_table = None

            new_consumption_data = gen_new_mediated_data(new_sample_site_info_table, \
                    matched_videos_table, arch_matched_videos_table, meta_id)
            old_consumption_data = gen_old_mediated_data(old_sample_site_info_table, \
                    matched_videos_table, arch_matched_videos_table, meta_id)
            new_consumption_data.to_csv(new_mediated_data_file, mode='a', header=None, index=False)
            old_consumption_data.to_csv(old_mediated_data_file, mode='a', header=None, index=False)

            meta_id = trackingMetas_fd.readline().replace('\n', '')

if __name__ == '__main__':
    main_func()
#   usage()
#   new_sample_site_info_table = sys.argv[1]
#   old_sample_site_info_table = sys.argv[2]
#   matched_videos_table = sys.argv[3]
#   arch_matched_videos_table = sys.argv[4]
#   new_mediated_data_file = 'new_consumption_file.csv'
#   old_mediated_data_file = 'old_consumption_file.csv'
#   new_consumption_data = gen_new_mediated_data(new_sample_site_info_table, \
#        matched_videos_table, arch_matched_videos_table)
#   old_consumption_data = gen_old_mediated_data(old_sample_site_info_table, \
#       matched_videos_table, arch_matched_videos_table)
#   new_consumption_data.to_csv(new_mediated_data_file, mode='a', header=None)
#   old_consumption_data.to_csv(old_mediated_data_file, mode='a', header=None)





