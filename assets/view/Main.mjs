// 尝试开发一个新闻资讯界面
fun jsNew(cls) {
    var obj = new(cls);
    obj.ctor();
    return obj;
}

class App
{   
    prop main;
    fun onDestroy() {
    }
    
	fun onCreate()
	{
	    Util.log("main function begin");
	    
	    var root = ViewDoc.rootView();
	    var appBox = root.itemByID(ViewGroup, "AppBox");
	    
        this.main = ViewDoc.createView(MainView, "boyia://layout/main.html");
	    this.main.initView();
	    
	    appBox.appendView(this.main);
	    appBox.draw();
	    appBox.commit();
	    JS_CallStaticMethod("com/boyia/app/utils/BoyiaUtils", "showToast", "(Ljava/lang/String;)V", "test mjs callstaticmethod");
	
	    Network.load("boyia://json/mock.json", App.loadCallback, App);
	}
	
	fun loadCallback(data)
	{
		
	    var obj = Util.json(data);
	    //Util.log(obj.app_version.last);
	    var categoryView = this.main.headerView.categoryView;
	    var size = obj.data.categoryList.size();
	    var view;
	    while (size > 0) 
	    {
	        size = size - 1;
	        var categoryItem = obj.data.categoryList.get(size);
	        
	        view = ViewDoc.createView(CategoryItem, "boyia://layout/category_item.html");
	        view.initView();
	        view.setTitle(categoryItem.title);
	        categoryView.appendView(view);
	    }
	    
	    var detailContainer = this.main.detailContainer;
	    var categoryItem = obj.data.categoryList.get(0);
	    var detailList = categoryItem.detailList;
	    size = detailList.size();
	    while (size > 0) {
	        size = size - 1;
	        var detailItem = detailList.get(size);
	        view = ViewDoc.createView(NewTextItem, "boyia://layout/news_text_item.html");
	        view.initView();
	        detailContainer.appendView(view);
	        view.setTitle(detailItem.title);
	        view.setInfo(detailItem.info1);
	        view.setImage(detailItem.image1);
	    }

	    this.main.draw();
	    this.main.commit();    
	}
}

fun getArea(data) {
    Util.log("getArea");
	var app_version = data.app_version;
    var area = data.startup_info.area_list.get(0);
	//var area_list = startup_info.area_list;
	//var area = area_list.get(0);
	Util.log(app_version.last);
	Util.log(area.name);
}

App.onCreate();