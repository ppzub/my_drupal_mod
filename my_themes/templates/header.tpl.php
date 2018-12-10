<h1>hook_theme за допомогою файлу шаблона</h1>

<h2 align="center"><?php print $variables['last_film_title']; ?></h2>
<div class=<?php print $variables['class'] ?> id=<?php print $variables['id'] ?> align="justify">
<?php print $variables['text'] ?>
</div>
<fieldset>
<legend><span class="fieldset-legend">  
<?php print $variables['title_fieldset'] ?></span></legend>
<div class="fieldset-wrapper" align="justify"> 
<?php print $variables['last_film_body'] ?></div></fieldset>
