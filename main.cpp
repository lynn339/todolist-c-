#include<iostream>
#include<string>
#include<vector>
/*第 1 步 Task：已經完成。還剩兩個小修改：把 #include <cstring> 換成 #include <string>，然後建構子的 done 給預設值 = false。
第 2 步 TodoList：題目已經出了，就等你寫。複習一下規格：
成員：vector<Task> tasks、int nextId
addTask(title)：回傳新任務的編號
markDone(id)
removeTask(id)：回傳 bool，找到並刪掉就回傳 true
printAll() const：每行印 [ ] 1. 標題，完成的印成 [x]，沒有任務時印 (沒有任務)*/

class Task{
    private:
        std::string title;
        int id;
        bool done;
    public:

        Task(std::string title, int id, bool done=false) : title(title), id(id), done(done){}
        int getId() const{
            return id;
        } // 取得id
        const std::string &getTitle() const//得到任務
        {
            return title;
        }
        bool isDone() const//是否完成
        {
            return done;
        }
        void markDone()//標示完成(user has to mark a task as done)
        {
            done = true;
        }
        virtual void print() const{
            
                
            if(done)
            {
                std::cout<< "[v]";
            }
            else{
                std::cout<<"[]";
            }
            std::cout<< id << ". " << title << std::endl; 
        }
};
// 這個類別是 Task 的子類別，表示有截止日期的任務
class DeadLineTask : public Task{
    private:
        std::string deadLine;
    public:
    // 呼叫父類別的建構子,因為父類別的建構子有三個參數,所以要呼叫父類別的建構子
        DeadLineTask(const std::string &title, int id, std::string deadline) : Task(title, id) 
        {
            this->deadLine = deadline;

        }
        void print() const override {
            if(isDone())
            {
                std::cout << "[v]";
            } 
            else{
                std::cout << "[]";
            }
            
            std::cout << getId()<< ". " << getTitle() << deadLine << std::endl;
        }

};

/*int addTask(const std::string &title)
{
    Task t(title, nextId);   // ①
    tasks.push_back(t);      // ②
    nextId++;                // ③
    return t.getId();        // ④
}*/

class ToDoList{
    private: 
        std::vector<Task> tasks;
        int nextId;
    public:
    ToDoList(){
        nextId = 1;
    }

    int addTask(const std::string &title)
    {
        Task t(title, nextId);
        tasks.push_back(t);
        nextId++;
        return t.getId();
    }

    void printAll() const{
        if(tasks.empty())
            {
                std::cout << "No task anymore!"<< std::endl;
            }
        else{
            for(const Task &task : tasks)
            {
                task.print();
            }
        }
         
    }
    void markDone(int id)
    {
        for(Task &task : tasks) // 要加&才是傳本人進去 不然不會改到
        {
            if(task.getId() == id)
            {
                task.markDone();
                return;
            }
        }
    }
    bool removeTask(int id)
    {
        for(int i = 0; i< tasks.size(); i++)
        {
            if(tasks[i].getId() == id)
            {
                tasks.erase(tasks.begin() + i);// 用i刪掉第i格
                return true;
            }
        }
        return false;
    }




};
int main()
{
   
    ToDoList list;
    list.printAll();                  // 空清單

    list.addTask("買牛奶");
    list.addTask("寫作業");
    list.addTask("洗衣服");
    list.markDone(2);
    list.printAll();

    std::cout << "刪 1 號：" << list.removeTask(1) << std::endl;
    std::cout << "刪 99 號：" << list.removeTask(99) << std::endl;
    list.printAll();
    DeadLineTask d("交報告", 4, "11/25");
    d.print();
}
