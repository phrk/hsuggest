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
f = open('queries.in', 'w')

def crawlPage(browser, pageid, f):
	url = "http://toster.ru/questions/latest?page="+str(pageid)
	browser.get(url)
	elems = browser.find_elements_by_class_name("questions_list_item")
	for elem in elems:
		f.write(elem.find_element_by_xpath("div[1]/div[1]/a[1]").text.encode('utf-8')+'\n')
	
for i in range(1, 10000):
	crawlPage(browser, i, f)
