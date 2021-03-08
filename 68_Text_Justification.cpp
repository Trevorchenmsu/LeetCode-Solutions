/*
solution: brute force
time: O(n^2)
space: O(1)
*/
class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> res;
        int idx = 0, len = words.size();
        
        while (idx < len) {
            // 添加第一个单词以及得到当前单词的长度
            string s = "";
            s += words[idx];
            int cnt = words[idx].length(); 
            
            // 获取每行能够得到的最大单词数。我们不在这里添加下一个单词，因为不确定单词间有多少空格          
            int next = idx + 1; 
            while (next < len) { 
                if (cnt + words[next].length() + 1 > maxWidth) // 超出长度限制
                    break;
                cnt += words[next++].length() + 1;
            }
            int diff = next - (idx + 1); // 得出当前指针与未来指针的差值
            
            /*
                diff=0表示上面的while循环没有执行或者第一步判定跳出，即无法添加下一个单词，因为超出长度限制
                next=len表示上面循环执行后一直前进累积到数组尽头，表示所有单词都可以被添加在一行。
                第一个for循环用来处理next=len的情况，对于diff=0的情况不起作用，因为next=idx+1。
                第二个for用来补充当前字符串长度不满足长度限制的情况，对于next=len和diff=0都适用。因为即便数组所有单词都添加
                到一整行，仍有可能不满足maxwidth，所以要补空格。同理，diff=0时无法加入下一个单词，但是当前单词长度也可能不足
                maxwidth，所以后面要继续补空格
            */
            if (next ==  len || diff == 0) {
                for (int i = idx + 1; i < next; i++) {
                    s += " ";
                    s += words[i];
                }
                
                for (int i = s.length(); i < maxWidth; i++) 
                    s += " ";
            }   
            /*
                下面属于需要在单词之间均布空格的情况。maxWidth-cnt表示需要添加的总空格数。diff可表示有多少block可以插入空格
                例如在3个数中，角标为0，1，2，diff=2，表示3个数之间有两个block可以插入空格。
                n表示在均分空格后还剩下多少个空格，然后把些剩余逐个从左到右分布给block。例如5%3=2，当我们给每个block均分1个时会
                剩下2个，那么如何分配这两个?按照题目的要求就是首先要均分，然后左侧空格优先多。所以对剩下2个的分配就会是，第1个block
                有1个额外空格，第2个block同理，第三个block，没有空格，所以分配是2，2，1
            */
            else {
                int spaces = (maxWidth - cnt) / diff;
                int n = (maxWidth - cnt) % diff;
                for (int i = idx + 1; i < next; i++) {
                    for (int j = spaces; j > 0; j--) 
                        s += " ";
                    
                    if (n > 0) {
                        s += " ";
                        n--;
                    }
                    // 这一步属于分配空格后正常的添加单词操作，即一个空格加一个单词
                    s += " ";
                    s += words[i];
                }
            }
            
            res.push_back(s);
            idx = next;
        }
        
        return res;
    }
};