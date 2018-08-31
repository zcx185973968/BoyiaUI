// 大规模JS编程
// 这个是数组类的定义
class Array {
    fun ctor() {
    }

    fun put(elem) {
        JS_AddInArray(this, elem);
    }

    fun get(idx) {
        return JS_GetFromArray(this, idx);
    }

	fun size() {
	    return JS_GetArraySize(this);
	}
	
	fun remove(elem) {
	    JS_RemoveFromArray(this, elem);
	}

	fun clear() {
	    JS_ClearArray(this);
	}
}