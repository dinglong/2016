# from django.conf.urls.defaults import *
from django.conf.urls import patterns, url, include
from blog.views import archive

urlpatterns = patterns('',
	url(r'^$', archive),
)
