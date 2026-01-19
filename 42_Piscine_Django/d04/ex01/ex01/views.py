from django.shortcuts import render


def django_page(request):
    """Display Django introduction page."""
    return render(request, 'ex01/django.html', {'page_name': 'django'})


def affichage_page(request):
    """Display static page process explanation."""
    return render(request, 'ex01/affichage.html', {'page_name': 'affichage'})


def templates_page(request):
    """Display template engine explanation."""
    return render(request, 'ex01/templates.html', {'page_name': 'templates'})
