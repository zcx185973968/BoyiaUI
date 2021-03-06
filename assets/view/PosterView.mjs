class PosterView extends ViewDoc
{
    prop image = null;
    prop textView = null;
    
    fun initView() {
        if (this.image == null) {
            this.image = this.itemByID(ImageView, "img");
        }

        //this.image.loadImage("https://ss0.baidu.com/6ONWsjip0QIZ8tyhnq/it/u=1832296905,803709198&fm=58");
        if (this.textView == null) {
            this.textView = this.itemByID(ViewGroup, "text");
        }

        this.addEventListener(1, this.touchDownCallback);
        //this.textView.setText("测试");
    }
    
    fun touchDownCallback() {
        this.setFocus(true);
    }
    
    fun setFocus(focus) 
    {        
        //this.posterImage();
        
        //var focus = Util.instanceof(PosterView, ImageView);
        if (focus)
        {
            //this.setLeft(this.left() - 25);
            //this.setStyle("poster_focus");
            this.startScale(120, 100);
            this.startOpacity(0, 500);
            //this.startTranslate(1000, this.top(), 500);
        }
        else
        {
            //this.startOpacity(255, 300);
            //this.setLeft(this.left() + 25);
            //this.setStyle("poster3");
        }
    }
}