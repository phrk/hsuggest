# -*- coding: utf-8 -*
import sys
import argparse
from selenium import webdriver
from selenium.common.exceptions import NoSuchElementException
from selenium.webdriver.common.keys import Keys
import time
import binascii
import string
import re
from subprocess import call
import subprocess
import os
import Image
import codecs
import md5

browser  = webdriver.Firefox()
f = open('so_queries.in', 'a')

def crawlPage(browser, pageid, f):
	url = "http://stackoverflow.com/questions?pagesize=50&sort=frequent&page="+str(pageid)
	browser.get(url)
	elems = browser.find_elements_by_class_name("question-summary")
	for elem in elems:
		f.write(elem.find_element_by_xpath("div[2]/h3[1]/a").text.encode('utf-8')+'\n')
		

for i in range(775, 13000):
	crawlPage(browser, i, f)

