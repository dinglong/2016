from django.template import loader, Context
from django.http import HttpResponse
from blog.models import BlogPost

def archive(request):
	posts = BlogPost.objects.all();
	template = loader.get_template("archive.html")
	context = Context({'posts' : posts})
	return HttpResponse(template.render(context))
