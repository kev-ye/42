from django.urls import path
from . import views

urlpatterns = [
    path('django', views.django_page, name='ex01_django'),
    path('affichage', views.affichage_page, name='ex01_affichage'),
    path('templates', views.templates_page, name='ex01_templates'),
]
